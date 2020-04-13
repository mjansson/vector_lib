# Vector Library  -  Public Domain

This library provides a cross-platform vector math library in C11 providing basic support data types and
functions to write applications and games in a platform-independent fashion. It provides:

* Vector (4-component)
* Matrix (4x4)
* Quaternion
* Transform (scale-rotate-translate)
* Utility (Euler angles)

It is written with the following API design principles in mind:

* Consistent. All functions, parameters and types should follow a well defined pattern in order to make it easy to remember how function names are constructed and how to pass the expected parameters.
* Orthogonal. A function should not have any side effects, and there should be only one way to perform an operation in the system.
* Specialized. A function in an API should perform a single task. Functions should not do completely different unrelated tasks or change behaviour depending on the contents of the variables passed in.
* Compact. The API needs to be compact, meaning the user can use it without using a manual. Note though that "compact" does not mean "small". A consistent naming scheme makes the API easier to use and remember.
* Contained. Third party dependencies are kept to an absolute minimum and prefer to use primitive or well-defined data types.
  
The latest source code maintained by Mattias Jansson is always available at

https://github.com/mjansson/vector_lib

This library is put in the public domain; you can redistribute it and/or modify it without any restrictions.

