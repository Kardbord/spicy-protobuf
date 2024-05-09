@load base/misc/version

module protobuf;

event zeek_init() &priority=20
	{
	# TODO: Our example here models a custom protocol sitting between
	# Ethernet and IP. The following sets that up, using a custom ether
	# type 0x88b5. Adapt as suitable, some suggestions in comments.
	local analyzer = PacketAnalyzer::ANALYZER_PROTOBUF;

	# Activate our analyzer on top of Ethernet.
	PacketAnalyzer::register_packet_analyzer(PacketAnalyzer::ANALYZER_ETHERNET, 0x88b5, analyzer);

	# Activate IP on top of our analyzer. 0x4950 is our own protocol's
	# magic number indicating that IP comes next.
	PacketAnalyzer::register_packet_analyzer(analyzer, 0x4950, PacketAnalyzer::ANALYZER_IP);

	# Alternative: Use this if your analyzer parses a link layer protocol directly.
	# const DLT_protobuf : count = 12345;
	# PacketAnalyzer::register_packet_analyzer(PacketAnalyzer::ANALYZER_ROOT, DLT_protobuf, analyzer);

	# Alternative: Use this if your analyzer parses a protocol running on top of
	# IPv4, using the specified IP protocol number.
	# PacketAnalyzer::register_packet_analyzer(PacketAnalyzer::ANALYZER_IP, 0xcafe, analyzer);

	# Alternative: Use this if you want your analyzer to run on top of UDP, activated on the specified well-known port.
	# const ports: set[port] = { 6789/udp } &redef;
	# PacketAnalyzer::register_for_ports(PacketAnalyzer::ANALYZER_UDP, analyzer, ports);
	}

# Example event defined in protobuf.evt.
event protobuf::packet(p: raw_pkt_hdr, payload: string)
	{
	# TODO: Consider just deleting this event handler if you don't need it.
	# For most packet analyzers, it's best to not do any script-level work
	# because the overhead could quickly become overwhelming.
	}
