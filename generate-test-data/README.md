# Generate Test Data Directory

This directory contains test files formatted as ascii text.  The `Protoscope` tool is leveraged to turn the text based files into protobuf raw binary data that can then be used to exercise the `spicy-protobuf` parsing capabilities.  

See the `Protoscope` installation instructions located at the reference below.

Command:
```bash
protoscope -s <test-file.txt> > ../test-data/<test-file.raw>
```

Example text based format:
```bash
field_num: value
1: 150
```
See the `Protoscope` [test data](https://github.com/protocolbuffers/protoscope/tree/main/testdata) directory for additional examples.  Specifically, the `*.golden` files.

## References

* [Protoscope](https://github.com/protocolbuffers/protoscope)
