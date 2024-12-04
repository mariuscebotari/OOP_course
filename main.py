import os
import time
from pathlib import Path
from datetime import datetime


# Base File class
class File:
    def __init__(self, path):
        self.path = Path(path)
        self.name = self.path.name
        self.extension = self.path.suffix
        self.creation_time = self.path.stat().st_ctime
        self.last_modified = self.path.stat().st_mtime

    def display_info(self):
        """Displays basic file information."""
        print(f"\nFile Name: {self.name}")
        print(f"Extension: {self.extension}")
        print(f"Creation Date: {datetime.fromtimestamp(self.creation_time)}")
        print(f"Last Modified Date: {datetime.fromtimestamp(self.last_modified)}")

    def has_changed(self):
        """Checks if the file has changed since the last snapshot."""
        current_mod_time = self.path.stat().st_mtime
        return current_mod_time != self.last_modified


# Derived class for Text Files
class TextFile(File):
    def __init__(self, path):
        super().__init__(path)

    def display_info(self):
        """Displays text file information including line, word, and character count."""
        super().display_info()
        line_count, word_count, char_count = 0, 0, 0
        with open(self.path, 'r') as file:
            for line in file:
                line_count += 1
                char_count += len(line)
                word_count += len(line.split())
        print(f"Line Count: {line_count}")
        print(f"Word Count: {word_count}")
        print(f"Character Count: {char_count}")


# Derived class for Image Files
class ImageFile(File):
    def __init__(self, path):
        super().__init__(path)

    def display_info(self):
        """Displays image file information including dimensions (if available)."""
        super().display_info()
        print("Note: Cannot extract dimensions without third-party libraries.")


# Derived class for Code Files
class CodeFile(File):
    def __init__(self, path):
        super().__init__(path)

    def display_info(self):
        """Displays code file information including line count, class count, and method count."""
        super().display_info()
        line_count, class_count, method_count = 0, 0, 0
        with open(self.path, 'r') as file:
            for line in file:
                line_count += 1
                if "class " in line:
                    class_count += 1
                if any(keyword in line for keyword in ("def ", "void ", "public ", "private ")):
                    method_count += 1
        print(f"Line Count: {line_count}")
        print(f"Class Count: {class_count}")
        print(f"Method Count: {method_count}")


# Manager class for handling files
class FileManager:
    def __init__(self, folder_path):
        self.folder_path = Path(folder_path)
        if not self.folder_path.exists():
            print(f"Folder '{self.folder_path}' does not exist. Creating it...")
            self.folder_path.mkdir(parents=True, exist_ok=True)
        self.files = []
        self.load_files()

    def load_files(self):
        """Loads files in the specified directory and initializes them based on their type."""
        self.files.clear()
        for file_path in self.folder_path.iterdir():
            if file_path.is_file():
                try:
                    if file_path.suffix == '.txt':
                        self.files.append(TextFile(file_path))
                    elif file_path.suffix in {'.py', '.java', '.cpp'}:
                        self.files.append(CodeFile(file_path))
                    elif file_path.suffix in {'.png', '.jpg'}:
                        self.files.append(ImageFile(file_path))
                    else:
                        self.files.append(File(file_path))
                except Exception as e:
                    print(f"Error loading file '{file_path.name}': {e}")

    def commit(self):
        """Updates the last modified times for all files as a new snapshot."""
        print("Committing snapshot...\n")
        for file in self.files:
            file.last_modified = file.path.stat().st_mtime
        print("Snapshot updated. All file statuses reset to 'clean'.")

    def status(self):
        """Displays whether each file has changed since the last snapshot."""
        print("\nFile Change Status:")
        for file in self.files:
            status = "changed" if file.has_changed() else "unchanged"
            print(f"{file.name}: {status}")

    def display_info(self, filename):
        """Displays information for a specific file."""
        file = next((f for f in self.files if f.name == filename), None)
        if file:
            file.display_info()
        else:
            print(f"File '{filename}' not found.")


# Main interactive loop
def main():
    folder_path = r"H:/Python Projects/OOP lab3/folder"  # Replace with actual folder path
    manager = FileManager(folder_path)

    print("Commands: commit, status, info <filename>, exit")

    while True:
        command = input("\nEnter command: ").strip().split(maxsplit=1)

        if not command:
            continue

        action = command[0].lower()

        if action == "commit":
            manager.commit()
        elif action == "status":
            manager.status()
        elif action == "info":
            if len(command) > 1:
                filename = command[1]
                manager.display_info(filename)
            else:
                print("Usage: info <filename>")
        elif action == "exit":
            print("Exiting program.")
            break
        else:
            print("Unknown command. Use 'commit', 'status', 'info <filename>', or 'exit'.")


if __name__ == "__main__":
    main()
