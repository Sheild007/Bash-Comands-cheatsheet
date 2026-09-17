# Data Wrangling Tutorial (Production Ready)

In a production environment, you rarely use `grep`, `awk`, or `sed` in isolation. You pipe (`|`) them together to extract, transform, and load (ETL) data from raw logs into actionable insights.

## Core Utilities for Pipelines

- **`head -n X` / `tail -n X`**: View the first/last `X` lines of a file or stream.
  - *Pro-tip*: `tail -f /var/log/syslog` follows a log file as it grows in real-time.
- **`wc -l`**: Word count. Specifically `-l` counts lines. Used to count how many matches you found.
- **`sort`**: Sorts lines of text alphabetically.
  - `-n`: Numeric sort.
  - `-r`: Reverse sort (descending).
  - `-k X`: Sort by the Xth column.
- **`uniq`**: Filters out adjacent repeated lines. 
  - *Crucial Rule*: You **MUST** `sort` data before piping to `uniq` for it to work properly on the whole file.
  - `-c`: Precedes each line with the number of times it occurred. (Amazing for finding top IP addresses or errors).

## The Production Pipeline Pattern
A typical log analysis command looks like this:
`cat logfile | grep "ERROR" | awk '{print $1}' | sort | uniq -c | sort -nr | head -n 5`
*(Get logs -> filter for errors -> extract the IP -> sort them -> count unique occurrences -> sort by highest count -> show top 5).*

---

## Production Scenarios (Exercises)

I have copied up to 5,000 lines of your actual system logs into `system_logs.txt`. I also generated a mock web server log at `access.log`. Use the pipelines discussed above to solve these problems.

### Scenario 1: Web Server Brute Force Analysis (`access.log`)
1. **Find the top 3 IP addresses making requests to the server.**
   *Hint: `awk` to extract IP (column 1) | `sort` | `uniq -c` | `sort -nr` | `head -n 3`*
2. **Find all IPs that received a `401` (Unauthorized) status code, and count how many times each IP failed.**
   *Hint: The HTTP status is the 9th column in standard access logs.*
3. **Count the total number of `500` (Internal Server Error) responses.**
   *Hint: Use `grep` or `awk` to find 500s, then pipe to `wc -l`.*

### Scenario 2: System Health Check (`system_logs.txt`)
*(Note: Because these are real logs from your machine, exact matches depend on what your system is doing, but the commands remain the same!)*

1. **Extract all error messages.** Try case-insensitive `grep` for "error", "fail", or "warn".
2. **Find out which daemon/service is logging the most.** 
   *Hint: In standard `journalctl` output or syslog, the service name is usually the 5th column (e.g., `systemd[1]:`). Extract it, sort, uniq -c, and find the top offenders.*
3. **Use `sed` to sanitize the log before sharing.** Replace all instance of your hostname (the 4th column in standard syslog) with the word "SERVER".
   *Hint: `sed 's/your_hostname/SERVER/g' system_logs.txt | head -n 20`*
