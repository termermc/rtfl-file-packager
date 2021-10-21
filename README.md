# rtfl-file-packager
Program that can package a file's contents into an Rtfl file

# Purpose
This program allows you to package a file's contents into an Rtfl variable.
This is useful for embedding help documents, templates, etc into Rtfl programs.

# Limitations
Since Rtfl string length is represented by a short integer, the maximum file size you can package is 32,767 bytes. That's about 32k ASCII characters, and about 8k Unicode CJK characters.