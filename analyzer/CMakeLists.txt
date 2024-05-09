spicy_add_analyzer(
    NAME protobuf
    PACKAGE_NAME spicy-protobuf
    SOURCES protobuf.spicy protobuf.evt zeek_protobuf.spicy
    SCRIPTS __load__.zeek main.zeek dpd.sig
)
