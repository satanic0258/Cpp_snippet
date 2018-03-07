@echo off
for /R %%f in (*.snippet) do convertSnippet.exe < "%%f"