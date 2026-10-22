# Task 3: YAML and Configuration Files

### Comparison of YAML and JSON

**1. Which format is easier for humans to read?**

YAML is generally easier for humans to read because it uses indentation and fewer symbols. It is suitable for configuration files because the settings and values are easy to understand.

**2. Which format is easier for machines to parse, and why?**

JSON is widely supported by programming languages and web APIs, making it a convenient format for exchanging data between applications. YAML can also be parsed by machines, but it requires an additional library in Python, such as PyYAML.

**3. Which format supports comments, and why does that matter?**

YAML supports comments using the `#` symbol. Comments help developers explain configuration settings and make files easier to maintain. Standard JSON does not support comments.

# Task 4: Comparing Formats and Columnar Thinking

### Part A: File Size Comparison

The program saves the same student data in JSON, XML, and YAML formats and measures their sizes in bytes.

The exact sizes depend on the number of records, indentation, and formatting. A smaller file may require less storage and transfer bandwidth, but file size alone does not determine which format is best.

### Part B: Row-Based and Columnar Access

The row-based function calculates the total GPA by visiting each student and reading the GPA field. The columnar function calculates the total directly from the GPA list.

Both functions return the same result. Columnar storage can be more efficient for analytical queries because the system can read only the columns needed for a calculation instead of reading every field in each record.

### Part C: Choosing the Right Format

**1. Public REST API for a mobile app — JSON**

I would choose JSON because it is supported by most programming languages and can be parsed easily by mobile applications and web browsers. It is a practical format for exchanging structured data between a server and a mobile app.

**2. Configuration file for a DevOps pipeline — YAML**

I would choose YAML because it is readable and supports comments. Developers can easily understand settings, explain important values, and maintain configuration files.

**3. Internal analytics system processing millions of records — Columnar format**

I would choose a columnar format such as Apache Parquet. Analytical queries often calculate sums, averages, and other statistics using only a few columns. Columnar storage reduces unnecessary data reads and can improve analytical performance.

**4. Internal microservice that must respond in under ten milliseconds — Protocol Buffers**

I would consider Protocol Buffers because it uses a compact binary representation and efficient serialization. This can reduce message size and processing overhead compared with text-based formats. However, the response-time requirement must be verified through benchmarking because network latency, application logic, and system load also affect performance.