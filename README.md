# Duplicate-Appendage
This program appends strings from one file to a duplicated version of itself, I developed it to test the principles shown in [this](https://www.youtube.com/watch?v=9pwMCHlNma4) video (messing with/triggering antiviruses based on static string-based signatures) but didn't find anything too interesting.

Usage:

Use the below syntax to have Duplicate-Appendage extract all (UNICODE or ASCII) strings from ``mimikatz.exe`` and append it to a duplicated version of ``DuplicateAppendage.exe`` located at ``output_file.exe``.

``DuplicateAppendage.exe mimikatz.exe output_file.exe``

A similar output could be achieved by dragging ``mimikatz.exe`` onto ``DuplicateAppendage.exe`` in ``explorer.exe``.

When testing your antivirus, static scanning might be insufficient - if you need to run the duplicated version of ``DuplicateAppendage.exe``, just double click it or execute it with no arguments provided, this will spawn it in a 'dummy' mode that does nothing while letting antivirus solutions scan it.

This can be built using ``cl.exe`` along with the ``/std:c++17`` compiler flag (I used ``std::filesystem`` pretty heavily and that requires ``C++17``).

Needless to say that this program isn't actually malicious in nature, although VirusTotal flagged this (5 engines detected it as a trojan) so check the source before you compile!
