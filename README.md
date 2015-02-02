SS for Qt
=========

## Super Simple library for Qt 5

The main idea of this library is to aggregate most useful operations in one
place. Qt is a great library and has the most incredible beautiful cross
platform implementation that I know. It is really great but we know that not
everything can be done in a generic way.

So, in this library, I'm addressing some of the specific needs that I usually
have when developing a software for Windows. The library does not only targets
Windows. It is built on top of Qt so to keep it cross platform. But it will
uses some Windows specific operations when required and when targeting that
platform.

## Version 1.3

Some changes in this version are note backward compatible with previous
versions. Current changes so far:

### Assets Module

This module was completely redesigned and are totaly different. Functions are
packed in the **assets** namespace that is not designed to be imported (that
means no `using namespace assets`). Read the documentation on @ref ssqt_assets
group.

