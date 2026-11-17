BEGIN {
    tcp = 0
    udp = 0
}
{
    # $1=event(received), $3=from node 2, $4=to node 3, $5=packet type
    if ($1 == "r" && $3 == "2" && $4 == "3" && $5 == "tcp")
        tcp++

    if ($1 == "r" && $3 == "2" && $4 == "3" && $5 == "cbr")
        udp++
}
END {
    printf("Total number of packets sent by TCP : %d\n", tcp)
    printf("Total number of packets sent by UDP : %d\n", udp)
}
