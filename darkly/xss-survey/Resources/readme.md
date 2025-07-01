# XSS (Cross-Site Scripting)
## Walk-Through
- Changing the value of options in the survey table rank, which affects the global rank of the members. From `<option value="1">1</option>` to `<option value="100">1</option>`

## Prevention
- Applying authorization checks, so only admins be allowed to reorder ranks, and verifying on the server that the current session’s user is indeed an admin before accepting any change.