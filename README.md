# Module Two SQL Injection Activity

[![CodeQL](https://github.com/rowland007/SQL-Injection-Activity/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/rowland007/SQL-Injection-Activity/actions/workflows/codeql-analysis.yml) [![CodeFactor](https://www.codefactor.io/repository/github/rowland007/sql-injection-activity/badge)](https://www.codefactor.io/repository/github/rowland007/sql-injection-activity)

## Overview

You are a senior software developer on a team of software developers who are responsible for a large banking web application. Your manager has learned that there has been a number of unauthorized uses of one of the company's systems. The other developers spent a lot of time tracing the issue, and they narrowed it down to some SQL queries running in the database that were modified from the queries created by the application. It allowed a hacker to get more data back than they were entitled to, including passwords. The other developers have tried a few things, but they don't know how to prevent it.

Following some guidance from an older testing guide, the developers were able to replicate the problem in a standalone test case including a standalone in-memory SQLite database. Doing this allowed them to reliably reproduce the SQL injection attack. However, they don’t know what to do next to prevent it from happening in the future. They came to you for help.

You will learn to do the following:

- Anticipate when a possible SQL injection attack is about to occur
- Write code to prevent a suspected SQL injection attack
- Decide how to react when there is an attempted SQL injection attack
- Protect your code from SQL injection attacks

## Prompt

This assignment presents code that creates an in-memory database and runs a number of queries with and without SQL injection, always dumping the results to the console. You need to modify the run_query() function to detect a potential SQL injection attack, prevent it, and display that information to the console. The specific type of SQL injection attack is the “OR value=value;” attack, and you must defend against that specific attack with value being any allowed SQL literal (numeric or quoted string).

The following are a few key notes:

- The source code has been commented using TODO to explain the detailed rules you must follow.
- There may be more than one way to solve this problem. It is key to demonstrate that your implementation prevents the SQL injection attack and displays the information to the console.
- Do not forget that you can leverage capabilities provided by the standard C++ library to help you achieve success.

Please comment on any changes you make in the code to explain the logic, formulas, or data types you are adding. You will also create a brief written summary of the approach taken, why it will stop the overflow or underflow, any issues you encountered, and how you resolved those issues.

Specifically, you will prepare the following:

- SQL injection defensive coding solutions
- C/C++ program functionality and best practices
- A summary of your process in a Word document that contains a screenshot of the application console output
