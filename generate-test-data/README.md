# Generate Test Data Directory

This directory contains test files formatted as ascii text (.txtpb).  The `Protoscope` tool is leveraged to turn the text based files into protobuf `binpb` binary data that can then be used to exercise the `spicy-protobuf` parsing capabilities.  

See the `Protoscope` installation instructions located at the reference below.

Command:

```bash
protoscope -s <test-file.txtpb> > ../test-data/<test-file.binpb>
```

Example text based format:

```bash
field_num: value
1: 150
```

To more easily view the contents of a .binpb file:

```bash
hexdump -C <test-file.binpb>
```

See the `Protoscope` [test data](https://github.com/protocolbuffers/protoscope/tree/main/testdata) directory for additional examples.  Specifically, the `*.golden` files.

## References

* [Protoscope](https://github.com/protocolbuffers/protoscope)
