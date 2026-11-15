BEGIN { count = 0 }
{
    if ($1 == "d")          # "d" means a packet was dropped
        count++
}
END {
    printf("Total packets dropped due to congestion: %d\n", count)
}