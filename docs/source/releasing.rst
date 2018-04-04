.. Copyright (c) 2017, Johan Mabille and Sylvain Corlay

   Distributed under the terms of the BSD 3-Clause License.

   The full license is in the file LICENSE, distributed with this software.

Releasing xplot
===============

Releasing a new version
-----------------------

From the master branch of xplot

- Make sure that you are in sync with the master branch of the upstream remote.
- In file ``xplot_config.hpp``, set the macros for ``XPLOT_VERSION_MAJOR``, ``XPLOT_VERSION_MINOR`` and ``XPLOT_VERSION_PATCH`` to the desired values.
- Update the readme file w.r.t. dependencies on xplot
- Stage the changes (``git add``), commit the changes (``git commit``) and add a tag of the form ``Major.minor.patch``. It is important to not add any other content to the tag name.
- Push the new commit and tag to the main repository. (``git push``, and ``git push --tags``)
