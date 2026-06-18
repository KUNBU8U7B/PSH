from pathlib import Path
import re

version = Path("CHANGELOG.txt")

def vers():
	if not version.exists() and not version.is_file():
		print("Error: no such file or directory")

	with open(version, 'r') as f:
		lines = f.read().strip()
		entries = re.split(r'\n\s*\n', lines)

		if not entries:
			print("CHANGELOG.txt is empty!")

		return entries[-1]

latest = vers()
print(f"Version: {latest}")