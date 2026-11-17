BEGIN {
    pkt = 0
    time = 0
}
{
    # $1=event (received), $3=LAN virtual node 8, $4=dest node 5, $6=packet size in bytes
    if ($1 == "r" && $3 == "8" && $4 == "5") {
        pkt += $6
        time = $2
    }
}
END {
    # Throughput formula: (total_bytes * 8 bits) / (time * 1,000,000) = Mbps
    printf("Throughput: %f Mbps\n", (pkt / time) * (8 / 1000000))
}
