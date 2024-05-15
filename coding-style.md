# Coding Standards

## Introduction

This document outlines the coding standards and guidelines that are followed in the project. Adhering to these standards ensures consistency, readability, and maintainability of the codebase.

## Naming Conventions

Naming conventions should follow:

- Functions: `functionsLikeThis()`
- Variables: `variables_like_this`
- Constants: `CONSTANTS_LIKE_THIS`
- Enums: `EnumLikeThis`
- Structs: `StructsLikeThis`
- Avoid using all uppercase names except for constants.

## Formatting Guidelines

- Indentation: Use 2 spaces for indentation, not tabs.
- Line Length: Keep lines limited to a maximum of 80 characters.
- Braces: Place opening braces on the same line as the control statement.
- Comments: Use descriptive comments to explain complex code sections. Follow a consistent commenting style.

## Coding Practices

- Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) for general formatting and style.
- Use meaningful variable and function names.
- Write clear and concise code. Avoid unnecessary complexity.

## Version Control

- Use Git for version control to manage the codebase effectively.
- Follow the Git branching model:
  - Create a new branch for each feature or bug fix.
  - Branch off from the `main` branch for development.
  - Name the branches descriptively, reflecting the feature or bug being addressed.
  - Avoid committing directly to the `main` branch.
  - Regularly merge feature branches back into `main` after thorough testing.

## Documentation

- Use Doxygen for documenting code to automatically generate API documentation.

  - Follow the [Doxygen](https://fnch.users.sourceforge.net/doxygen_c.html) syntax for comments to document functions, variables, and code blocks.
  - Include brief descriptions, parameter descriptions, return value descriptions, and example usage in the comments.
  - Make sure to provide descriptive and meaningful documentation to enhance code understanding.
  - Use Doxygen tags such as `@brief`, `@param`, `@return`, `@example`, etc., to structure the comments properly.

- Set yourself as the author in the file header comments if you create new files or significant sections of code.
- If you modify an existing file, add a `@section Modifications` below the file header comments and provide details of the changes made.

  - Include a brief description of the modifications and specify the date and your name.
  - Here's an example of how to document modifications:

    ```c
    /**
     * @file example.c
     * @brief Example file signature.
     *
     * @version 0.1
     * @date 2024-03-20
     * @section Modifications
     * - 2024-03-25: Updated (...).
     *   [Your Name]
     */
    ```

## Conclusion

Adhering to these coding standards is essential for maintaining a high-quality codebase. By following these guidelines, we ensure consistency across the project and make it easier for developers to understand, contribute to, and maintain the code.
