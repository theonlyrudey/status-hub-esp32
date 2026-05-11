# Agent Runtime Status Rule

For every task in this repository, agents must report execution state to StatusHub.

Required command format:

```bash
statushub-set -d '{"status":"HERE_IS_THE_STATUS","meta":{"source":"agent"}}'
```

Required transitions:

1. At task start:
```bash
statushub-set -d '{"status":"working","meta":{"source":"agent"}}'
```
2. On successful completion:
```bash
statushub-set -d '{"status":"finished","meta":{"source":"agent"}}'
```
3. On failure/blocker/abort:
```bash
statushub-set -d '{"status":"error","meta":{"source":"agent"}}'
```
4. When explicitly idle and waiting for next task:
```bash
statushub-set -d '{"status":"idle","meta":{"source":"agent"}}'
```

This is mandatory for every run.
