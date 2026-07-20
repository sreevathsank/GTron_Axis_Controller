#!/usr/bin/env python3
"""
Intel HEX to Binary Converter for ATSAMC21
Converts .hex files to .bin files
Fixes the issue with high memory addresses (config bits)
"""

import sys
import os

def convert_hex_to_bin_smart(hex_filename, bin_filename=None, max_address=0x40000, verbose=False):
    """
    Smart converter that only extracts the main program area,
    ignoring configuration bits at high addresses
    
    Args:
        hex_filename: Input HEX file path (.hex)
        bin_filename: Output BIN file path (optional, auto-generated if None)
        max_address: Maximum address to include (default 256KB for ATSAMC21)
        verbose: Print detailed information
    """
    
    # Check if input file has .hex extension
    if not hex_filename.lower().endswith('.hex'):
        print("WARNING: Input file '" + hex_filename + "' doesn't have .hex extension")
        response = input("Do you want to continue? (y/n): ")
        if response.lower() != 'y':
            return False
    
    # Auto-generate output filename if not provided
    if bin_filename is None:
        base_name = os.path.splitext(hex_filename)[0]
        bin_filename = base_name + '.bin'
    
    print("Converting: " + hex_filename + " -> " + bin_filename)
    print("-" * 50)
    
    memory = {}
    extended_addr = 0
    ignored_count = 0
    
    try:
        with open(hex_filename, 'r') as hex_file:
            line_num = 0
            for line in hex_file:
                line_num += 1
                line = line.strip()
                
                # Skip empty lines
                if not line or line[0] != ':':
                    continue
                
                # Parse Intel HEX line
                line = line[1:]
                byte_count = int(line[0:2], 16)
                address = int(line[2:6], 16)
                record_type = int(line[6:8], 16)
                
                # Process based on record type
                if record_type == 0x00:  # Data record
                    addr = extended_addr + address
                    
                    # IGNORE data above main program area
                    if addr >= max_address:
                        if verbose:
                            print("Line " + str(line_num) + ": Ignoring data at 0x" + format(addr, '08X') + " (config/fuse bits)")
                        ignored_count += byte_count
                        continue
                    
                    # Store data bytes
                    for i in range(byte_count):
                        byte_pos = 8 + (i * 2)
                        memory[addr + i] = int(line[byte_pos:byte_pos + 2], 16)
                
                elif record_type == 0x04:  # Extended Linear Address
                    extended_addr = int(line[8:12], 16) << 16
                    if verbose:
                        print("Line " + str(line_num) + ": Extended address set to 0x" + format(extended_addr, '08X'))
                
                elif record_type == 0x01:  # End of file
                    if verbose:
                        print("Line " + str(line_num) + ": End of file")
                    break
                
                elif record_type == 0x02:  # Extended Segment Address
                    extended_addr = int(line[8:12], 16) << 4
                    if verbose:
                        print("Line " + str(line_num) + ": Segment address set to 0x" + format(extended_addr, '08X'))
    
    except FileNotFoundError:
        print("ERROR: File '" + hex_filename + "' not found!")
        print("Make sure the .hex file exists in the current directory or provide the full path")
        return False
    except Exception as e:
        print("ERROR: " + str(e))
        return False
    
    # Check if we found any data
    if not memory:
        print("ERROR: No valid data found in HEX file!")
        return False
    
    # Get the actual program range
    min_addr = min(memory.keys())
    max_addr = max(memory.keys())
    total_bytes = len(memory)
    
    print("\nMemory Analysis:")
    print("  Program start:     0x" + format(min_addr, '08X'))
    print("  Program end:       0x" + format(max_addr, '08X'))
    print("  Address range:     " + str(max_addr - min_addr + 1) + " bytes")
    print("  Actual data bytes: " + str(total_bytes) + " bytes")
    
    if ignored_count > 0:
        print("  Ignored bytes:     " + str(ignored_count) + " bytes (config/fuse bits)")
    
    # Calculate gaps
    expected_bytes = max_addr - min_addr + 1
    gaps = expected_bytes - total_bytes
    if gaps > 0:
        print("  Gaps in data:      " + str(gaps) + " bytes (will be filled with 0xFF)")
    
    # Write binary file
    print("\nWriting binary file...")
    with open(bin_filename, 'wb') as bin_file:
        bytes_written = 0
        for addr in range(min_addr, max_addr + 1):
            if addr in memory:
                bin_file.write(bytes([memory[addr]]))
            else:
                bin_file.write(bytes([0xFF]))  # Fill gaps with 0xFF
            bytes_written += 1
    
    # Get output file size
    output_size = os.path.getsize(bin_filename)
    
    print("Success! Created: " + bin_filename)
    print("Output file size: " + str(output_size) + " bytes (" + str(round(output_size/1024, 1)) + " KB)")
    
    # Sanity check
    if output_size > 1024 * 1024:  # 1MB warning
        print("\nWARNING: Output file is larger than expected!")
        print("This might indicate an issue with the conversion.")
    
    return True

def main():
    """
    Main function for command-line usage
    """
    print("=" * 50)
    print("Intel HEX to Binary Converter")
    print("For ATSAMC21 and similar microcontrollers")
    print("=" * 50)
    
    # Check command-line arguments
    if len(sys.argv) < 2:
        print("\nUsage:")
        print("  python " + sys.argv[0] + " <input.hex> [output.bin] [--verbose]")
        print("\nExamples:")
        print("  python " + sys.argv[0] + " firmware.hex")
        print("  python " + sys.argv[0] + " firmware.hex output.bin")
        print("  python " + sys.argv[0] + " firmware.hex output.bin --verbose")
        print("\nNote: Input file should have .hex extension")
        sys.exit(1)
    
    # Parse arguments
    hex_file = sys.argv[1]
    bin_file = sys.argv[2] if len(sys.argv) > 2 and not sys.argv[2].startswith('--') else None
    verbose = '--verbose' in sys.argv or '-v' in sys.argv
    
    # Check if input file exists
    if not os.path.exists(hex_file):
        print("\nERROR: Input file '" + hex_file + "' does not exist!")
        
        # Try adding .hex extension if not present
        if not hex_file.endswith('.hex'):
            hex_file_with_ext = hex_file + '.hex'
            if os.path.exists(hex_file_with_ext):
                print("Found file: " + hex_file_with_ext)
                hex_file = hex_file_with_ext
            else:
                print("Please check the filename and path")
                sys.exit(1)
        else:
            print("Please check the filename and path")
            sys.exit(1)
    
    # Perform conversion
    success = convert_hex_to_bin_smart(hex_file, bin_file, verbose=verbose)
    
    if success:
        print("\nConversion completed successfully!")
        sys.exit(0)
    else:
        print("\nConversion failed!")
        sys.exit(1)

if __name__ == "__main__":
    main()