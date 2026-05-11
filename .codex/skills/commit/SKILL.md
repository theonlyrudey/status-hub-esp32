---
name: commit
description: Stage current workspace changes, create a concise 4-6 word commit message, commit, and push to the current branch. Use when the user says "commit" or asks to commit/push current changes without providing a full git command sequence.
---

# Commit

Execute this workflow when the user asks to commit current changes.

## Workflow

1. If this repository requires status updates, set task status to `working` before git actions.
2. Inspect changes with `git status --short`.
3. If there are no tracked or untracked changes, report that there is nothing to commit and stop.
4. Stage everything with `git add -A`.
5. Create a commit message of exactly 4 to 6 words.
6. Commit with `git commit -m "<message>"`.
7. Detect the current branch with `git branch --show-current`.
8. Push with `git push origin <current-branch>`.
9. If step 6 or 8 fails, report the failure clearly and set required repo status to `error` when such policy exists.
10. If commit and push succeed, set required repo status to `finished` when such policy exists.

## Message Rules

- Keep the message specific to the actual diff.
- Use plain words, no trailing period.
- Keep length strictly between 4 and 6 words.

## Execution Notes

- Do not run destructive git commands.
- Do not amend existing commits unless the user explicitly asks.
- If push is rejected, report the rejection reason and stop for user direction.
