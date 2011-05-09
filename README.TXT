General
=======

Cpp-Markdown is a freely-available Markdown text-to-HTML translator, written in
C++, intended for integration into C++ programs rather than for use in web
applications.

It differs from other Markdown translators in a few ways:

* It's written in C++, making full use of C++ constructs such as classes,
  inheritance, I/O streams, and namespaces. This means that you get the full
  speed advantages of a compiled language, as well as easier integration into
  C++ programs.

* It's a more accurate implementation of the [Markdown specification][1] than
  most of the currently-available ones. Its first release passes all 23 tests in
  the Markdown test suite, and 12 of the 17 tests in the PHP Markdown test
  suite, of [MDTest 1.1][2].

* It is fully os-independent. It understands files that use DOS/Windows CR/NL
  line endings, Mac OSX CR line endings, or UNIX/Linux NL line endings. It is
  also designed to work with UTF-8 files, and can be extended to work with
  Unicode (UTF-16/UCS-2 or UTF-32/UCS-4) files with minimal effort.

* It is *not* a port of another existing implementation, but was written from
  scratch. That means you can use it in your own programs without worrying about
  any license other than Cpp-Markdown's own very permissive one.

This README file is written in Markdown format, and an HTML version (translated
by the stand-alone Cpp-Markdown program) is provided as well, so you can see
exactly what it does.

 ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

Why?
====

I originally wrote it because I wanted to use the Markdown format in one of my
own C++ projects, and there was no existing C or C++ implementation that I
liked. I'm releasing it as open-source because Markdown is an excellent and
well-thought-out format, and I'd like to see it available in more programs.

 ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

Requirements
============

Cpp-Markdown is designed for integration into C++ programs. For that purpose,
you only need a C++ compiler, a few of the header-only libraries from the [Boost
project][3] (version 1.36 or later, due to the use of the `Boost::Unordered`
library), and a compiled version of the `Boost::Regex` library. I tried writing
it without using regular expressions, but it was a *lot* harder, and I gave up
after a few days.

I've also provided the small `main.cpp` file that I use for testing it, and the
`Boost::Jam` file that will compile it into an executable. With those, you can
create a stand-alone program that can read text from the standard input or a
file and write the corresponding HTML to standard output.

 ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

Usage
=====

Integration into C++ programs
-----------------------------

To use it in a C++ program:

* Add `markdown.cpp` and `markdown-tokens.cpp` to your project (as well as the
  `Boost::Regex` library, if you don't already have it);
* Add an `#include "markdown.h"` line in the file(s) you want to use it in.
* Create a `markdown::Document` object, feed it some input via `string`s or
  `istream`s through one of the `read` functions, and call the member function
  `write` to write out the HTML code to an `ostream`. (See the included
  `main.cpp` for a working example.)

It's that simple. The stream design means that you can read from an in-memory
string, the keyboard, a file, or any other input device with ease, and write to
a file, an in-memory string, or any output device just as simply.

Stand-alone program
-------------------

The stand-alone `cpp-markdown` program is very minimal. Run it with the `-?` or
`--help` parameters to get usage help.

 ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

History
=======

Version 1.00 (February 20th, 2009)
----------------------------------

First public release.

 ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

To-Do
=====

I don't expect that this library will require many updates. It's pretty close to
done already, at least until a new version of the Markdown format is released.

There *are* a few things that I'd like to add to it, as time permits, such as
explicit `wchar_t` support (for Unicode). I'd also like to improve its score on
the PHP-Markdown test suite, for those last few tests that it presently fails.
There are at least two tests that it will never fully pass (because it handles
invalid nesting differently than PHP-Markdown does), but the others should be
passable with a little more tweaking.

 ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

License
=======

Cpp-Markdown is released under the MIT license. See the LICENSE.TXT file that
accompanies this distribution for all the details that only a lawyer could love,
but the general idea is that you can do pretty much anything you want with the
code except claim that it's your own work.



[1]: http://daringfireball.net/projects/markdown/syntax
[2]: http://six.pairlist.net/pipermail/markdown-discuss/2007-September/000815.html
[3]: http://www.boost.org/
