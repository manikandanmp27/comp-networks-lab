{
    # Column 1 = timestamp, Column 6 = variable name ("cwnd_"), Column 7 = cwnd value
    if ($6 == "cwnd_")
        printf("%f\t%f\n", $1, $7)
}
