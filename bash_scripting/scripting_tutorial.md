# Bash Scripting: Putting It All Together

Writing one-liners is great for ad-hoc analysis, but for production tasks (like daily reports, automated alerts, or log rotation), you write Bash scripts.

## Key Concepts for Scripting

1. **Shebang**: Always start your scripts with `#!/bin/bash`.
2. **Variables**: `LOG_FILE="access.log"`. (No spaces around `=`).
   - Access them with `$LOG_FILE`.
3. **Command Substitution**: Assign the output of a command to a variable.
   - `ERROR_COUNT=$(grep "ERROR" $LOG_FILE | wc -l)`
4. **Arguments**: `$1`, `$2`, etc. represent arguments passed to the script. `$#` is the number of arguments.
5. **Conditionals (If Statements)**:
   ```bash
   if [ "$ERROR_COUNT" -gt 100 ]; then
       echo "CRITICAL: Too many errors!"
   else
       echo "Status normal."
   fi
   ```
6. **Loops (For / While)**:
   ```bash
   for file in $(find /path -name "*.log"); do
       echo "Processing $file"
   done
   ```

---

## The Final Exercise

I have provided a skeleton script called `log_analyzer.sh`. Your task is to open it in an editor and fill in the missing commands based on what you've learned from `grep`, `awk`, `find`, and data pipelines.

**Goal:** Create a script that takes a directory as an argument, finds all `.log` files inside it, and generates a summary report of errors and top IP addresses.

### Steps to complete:
1. Open `log_analyzer.sh`.
2. Read the comments starting with `TODO:`.
3. Write the appropriate pipeline/command.
4. Make the script executable: `chmod +x log_analyzer.sh`
5. Run it against your `data_wrangling` directory: `./log_analyzer.sh ../data_wrangling/`
