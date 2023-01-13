# woody-woodpacker

Packer ELF 64 bits.

This program duplicate another program with instructions ciphered.
Instructions are deciphered at the start of this program.

42 Paris school virus project.

## Build
Compilation :
```
make
```

Clean objects files :
```
make clean
```

Clean entire project :
```
make fclean
```

## Usage
```
Usage: ./woody-woodpacker [OPTIONS]... [FILE]                                                                                                                                       
        -v              Verbose mode                                                                                                                                                
        -s              Display sections informations                                                                                                                               
        -c              Display injected opcode                                                                                                                                     
        -k hexnum       Set encryption key
```
