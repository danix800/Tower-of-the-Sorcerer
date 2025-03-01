#!/usr/bin/env python3
import os
import re
import sys
import tempfile
import shutil

def has_cstdio_include(content):
    """Check if file already has cstdio include."""
    return re.search(r'#include\s+<cstdio>', content) is not None

def add_cstdio_include(content):
    """Add cstdio include after the last include statement."""
    if has_cstdio_include(content):
        return content
    
    include_pattern = re.compile(r'(#include\s+[<"][^>"]*[>"])', re.MULTILINE)
    matches = list(include_pattern.finditer(content))
    
    if not matches:
        # No includes found, add at the beginning
        return "#include <cstdio>\n\n" + content
    
    # Add after the last include
    last_include = matches[-1]
    position = last_include.end()
    return content[:position] + "\n#include <cstdio>" + content[position:]

def find_functions(content):
    """Find all function declarations/definitions in the file."""
    # Pattern for function definitions (with body)
    # This is a simplified pattern and may need adjustments
    function_pattern = re.compile(r'((?:virtual\s+)?(?:static\s+)?(?:[\w:]+\s+)+[\w:]+\s*\([^)]*\)(?:\s*const)?(?:\s*override)?)\s*{', re.MULTILINE)
    
    functions = []
    for match in function_pattern.finditer(content):
        func_signature = match.group(1).strip()
        start_pos = match.end() - 1  # Position right after the opening '{'
        functions.append((func_signature, start_pos))
    
    return functions

def add_debug_statements(content, file_path):
    """Add debug printf statements to each function in the file."""
    functions = find_functions(content)
    
    # We need to add statements from the end to avoid changing positions
    functions.reverse()
    
    modified_content = content
    for func_signature, start_pos in functions:
        # Clean up the function signature for the debug message
        clean_signature = func_signature.replace('\n', ' ').strip()
        # Remove return type and get just the function name
        func_parts = clean_signature.split()
        func_name = func_parts[-1]
        # Handle cases where function name has parameters attached
        if '(' in func_name:
            func_name = func_name[:func_name.find('(')]
        
        # Get just the filename without path
        file_name = os.path.basename(file_path)
        
        # Create debug messages
        entry_msg = f'\n    printf("DEBUG: Entering {file_name}::{func_name}\\n");'
        exit_msg = f'\n    printf("DEBUG: Exiting {file_name}::{func_name}\\n");'
        
        # Add entry message right after the opening '{'
        modified_content = modified_content[:start_pos+1] + entry_msg + modified_content[start_pos+1:]
        
        # We need to find the matching closing brace for this function
        # This is complex in general, but a simplified approach:
        # Count braces from the start position
        brace_count = 1
        pos = start_pos + 1 + len(entry_msg)
        
        while pos < len(modified_content) and brace_count > 0:
            if modified_content[pos] == '{':
                brace_count += 1
            elif modified_content[pos] == '}':
                brace_count -= 1
            pos += 1
        
        if brace_count == 0:
            # Found the matching closing brace
            close_brace_pos = pos - 1
            # Add exit message right before the closing '}'
            modified_content = modified_content[:close_brace_pos] + exit_msg + modified_content[close_brace_pos:]
    
    # Add cstdio include if needed
    return add_cstdio_include(modified_content)

def process_file(file_path):
    """Process a single CPP file to add debug statements."""
    print(f"Processing {file_path}")
    
    # Create a backup
    backup_path = file_path + ".bak"
    shutil.copy2(file_path, backup_path)
    
    with open(file_path, 'r', encoding='utf-8') as f:
        original_content = f.read()
    
    try:
        modified_content = add_debug_statements(original_content, file_path)
        
        # Write the modified content to a temporary file first
        with tempfile.NamedTemporaryFile(mode='w', delete=False, encoding='utf-8') as temp:
            temp.write(modified_content)
            temp_name = temp.name
        
        # Then move it to replace the original
        shutil.move(temp_name, file_path)
        print(f"Successfully modified {file_path}")
    except Exception as e:
        # Restore from backup on error
        shutil.copy2(backup_path, file_path)
        print(f"Error processing {file_path}: {e}")
        return False
    
    return True

def process_all_cpp_files(cpp_files_list):
    """Process all CPP files listed in the given file."""
    with open(cpp_files_list, 'r') as f:
        cpp_files = f.read().splitlines()
    
    success_count = 0
    for file_path in cpp_files:
        if process_file(file_path):
            success_count += 1
    
    print(f"Processed {success_count} out of {len(cpp_files)} files successfully")

if __name__ == "__main__":
    if len(sys.argv) > 1:
        cpp_files_list = sys.argv[1]
    else:
        cpp_files_list = "/tmp/cpp_files.txt"
    
    if not os.path.exists(cpp_files_list):
        print(f"Error: {cpp_files_list} does not exist")
        sys.exit(1)
    
    process_all_cpp_files(cpp_files_list)