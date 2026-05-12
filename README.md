# AgentNotificator HTTP API

This project exposes a status update endpoint on the ESP32:

- `POST /status`

## Request

### Headers

- `Content-Type: application/json`

### JSON body

```json
{
  "status": "working",
  "meta": {
    "source": "ci-runner",
    "message": "Compiling project"
  }
}
```

### Rules

- `status` is required, string.
- Allowed `status` values: `idle`, `working`, `finished`, `error`.
- `meta` is optional.
- `meta.source` is optional string, max length `31`.
- `meta.message` is optional string, max length `95`.
- If `meta.source` is not provided, server uses `"http-api"`.

### JSON Schema (draft-style)

```json
{
  "type": "object",
  "required": ["status"],
  "properties": {
    "status": {
      "type": "string",
      "enum": ["idle", "working", "finished", "error"]
    },
    "meta": {
      "type": "object",
      "properties": {
        "source": {
          "type": "string",
          "maxLength": 31
        },
        "message": {
          "type": "string",
          "maxLength": 95
        }
      },
      "additionalProperties": true
    }
  },
  "additionalProperties": true
}
```

## Responses

### `200 OK`

```json
{
  "ok": true,
  "status": "working",
  "receivedAtMs": 123456,
  "source": "ci-runner"
}
```

### `400 Bad Request`

```json
{
  "ok": false,
  "error": "Field 'status' is required and must be a string."
}
```

## Smoke test with curl

Replace `<DEVICE_IP>` with your ESP32 IP from serial logs.

```bash
curl -i -X POST "http://<DEVICE_IP>/status" \
  -H "Content-Type: application/json" \
  -d '{"status":"working","meta":{"source":"manual-test"}}'
```

Invalid status example:

```bash
curl -i -X POST "http://<DEVICE_IP>/status" \
  -H "Content-Type: application/json" \
  -d '{"status":"unknown"}'
```
