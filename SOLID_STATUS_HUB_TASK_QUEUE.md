# ESP32 Status Hub - SOLID Task Queue

## Purpose
Build this project into a non-blocking, event-driven status hub on ESP32:
- receives status updates via HTTP API
- notifies listeners through broadcaster/listener flow
- runs display animations without blocking API handling
- stays ready for future OLED migration

## Design Rules (applies to all tasks)
- Use interfaces for interchangeable components.
- No `delay()` in runtime flow.
- Use `tick(nowMs)` for periodic work.
- Keep status changes event-based (publisher -> listeners).
- Keep hardware-specific code behind interfaces.
- Favor small classes with single responsibility.

## Target Architecture (high level)
- `StatusHub` (status state + broadcaster)
- `IStatusListener` (already exists, keep and extend if needed)
- `ITickable` (new runtime contract)
- `ApiHttpController` (`ITickable`, parses HTTP JSON, publishes status change requests)
- `AnimationController` (`ITickable`, frame timing/state machine)
- `IDisplayBackend` (device abstraction)
  - `Max72xxDisplayBackend` (current)
  - `OledDisplayBackend` (future)
- `DisplayStatusListener` (listens to status changes and drives animation/display intent)
- `AppRuntime` (`ITickable` registry + main loop coordinator)

## Step-by-Step Queue

1. [X] Add a task runtime interface
- Create `src/Core/ITickable.h` with:
  - `virtual void tick(uint32_t nowMs) = 0;`
- Keep it tiny and framework-agnostic.
- Done when project compiles with interface added.

2. [X] Introduce runtime coordinator
- Add `src/Core/AppRuntime.h/.cpp`.
- Responsibilities:
  - register/unregister `ITickable*`
  - call all `tick(nowMs)` in `loop()`
- Done when `main.cpp` delegates runtime work only through `AppRuntime`.

3. [X] Strengthen status domain model (open for extension)
- Keep enum-like status values for now.
- Add conversion helpers in `src/StatusController/StatusCodec.h/.cpp`:
  - `bool tryParseStatus(const String&, Status&)`
  - `const char* toString(Status)`
- Done when conversion logic is not duplicated in display/API code.

4. [X] Add status event payload object
- Create `src/StatusController/StatusEvent.h`:
  - `Status status`
  - optional metadata fields (source, message)
  - timestamp (`uint32_t receivedAtMs`)
- Keep listener API compatible first, then migrate.
- Done when status change can carry metadata without breaking display flow.

5. [X] Evolve broadcaster/listener contract
- Decide one of:
  - keep `onStatusChanged(Status)` and add second method for event payload
  - or migrate directly to `onStatusChanged(const StatusEvent&)`
- Update `StatusHub` to notify all listeners from one place.
- Done when listeners react only via broadcaster notifications.

6. [X] Introduce display abstraction for future OLED
- Add `src/Display/IDisplayBackend.h` with operations such as:
  - `clear()`
  - `drawBitmap8x8(const uint8_t bitmap[8])`
  - `present()`
- Wrap current MAX72XX logic into `Max72xxDisplayBackend`.
- Done when `DisplayController` depends on `IDisplayBackend`, not `MD_MAX72XX`.

7. [X] Add animation model (data + timing, no hardware)
- Create `src/Display/Animation/`:
  - `AnimationFrame` (`bitmap + durationMs`)
  - `AnimationSequence` (list of frames, loop mode)
  - `AnimationStateMachine`
- Done when animations can advance by time only (`nowMs`), no direct IO.

8. [X] Add animation runner (`ITickable`)
- Create `AnimationController` implementing `ITickable`.
- On each tick:
  - check frame timing
  - render next frame through `IDisplayBackend`
- Done when `Working` status can animate while system stays responsive.

9. [X] Add status-to-animation mapping listener
- Create `DisplayStatusListener` (implements `IStatusListener`).
- Responsibility:
  - map incoming status to animation/bitmap mode
  - command `AnimationController` (not raw display drawing)
- Done when status changes update visual mode immediately and cleanly.

10. [ ] Add Wi-Fi bootstrap module
- Create `src/Network/WifiManager.h/.cpp`.
- Responsibilities:
  - connect to WLAN
  - expose current IP via Serial logs
  - optional mDNS hostname (e.g. `agent-hub.local`)
- Done when device reliably connects and logs reachable address.

11. [ ] Add HTTP API module (`ITickable`)
- Create `src/Api/ApiHttpController.h/.cpp` using Arduino WebServer first.
- Start with one endpoint:
  - `POST /status`
- Input JSON:
  - required `status` string
  - optional `meta` object
- On valid payload:
  - publish status event through `StatusHub`
- On invalid payload:
  - return `400` with error JSON
- Done when API updates status without blocking animation.

12. [ ] Keep JSON handling isolated
- Add `src/Api/StatusRequestParser.h/.cpp`.
- Parse/validate JSON in one place only.
- Done when controller does not contain low-level JSON parsing logic.

13. [ ] Wire composition root in `main.cpp`
- Compose dependencies in one place:
  - backend, status hub, listeners, animation, API, Wi-Fi, runtime
- `setup()`:
  - init hardware/network/modules
  - register listeners/tickables
- `loop()`:
  - `runtime.tick(millis())`
- Done when `main.cpp` is mostly orchestration and has minimal logic.

14. [ ] Add lightweight diagnostics
- Add serial logs for:
  - wifi connected + IP
  - API request accepted/rejected
  - status transitions
- Done when behavior is observable during bring-up.

15. [ ] Add host-side API smoke checks
- Document example commands in `README`:
  - `curl -X POST http://agent-hub.local/status ...`
- Add expected responses.
- Done when you can verify behavior from terminal quickly.

16. [ ] Optional: internal queue for burst updates
- If rapid updates appear, add a small bounded event queue between API and hub.
- Keep deterministic policy (`drop oldest` or `drop newest`).
- Done when burst behavior is defined and documented.

17. [ ] Prepare migration seam for broadcast later
- Define interface now (do not implement yet):
  - `IStatusPublisher` or `IOutboundStatusNotifier`
- Future module can push websocket/SSE/MQTT without changing core domain.
- Done when adding outbound broadcast later requires only a new module.

## Suggested Implementation Order (practical)
1) Steps 1-3  
2) Steps 6-9  
3) Steps 10-13  
4) Steps 14-15  
5) Steps 16-17 (only if needed)

## Acceptance Criteria for MVP
- `POST /status` changes state with validation.
- Display reacts immediately to status changes.
- `Working` animation runs smoothly.
- No blocking calls in loop path.
- Components communicate via interfaces/events.
- Architecture allows replacing MAX72XX backend with OLED backend.
