BEGIN {
    count = 0
}
{
    if ($1 == "d") # "d" stands for dropped packet
        count++
}
END {
    printf("The Total no of Packets Dropped due to Congestion: %d\n", count)
}
