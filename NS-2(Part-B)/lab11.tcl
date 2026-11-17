set ns [new Simulator]

# Open trace and NAM animation files
set tf [open lab1.tr w]
$ns trace-all $tf
set nf [open lab1.nam w]
$ns namtrace-all $nf

# Create 4 nodes (2 sources, 1 router, 1 destination)
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Colors for traffic packets in NAM
$ns color 1 "red"
$ns color 2 "blue"

# Labels for nodes in NAM
$n0 label "Source 1 (Red)"
$n1 label "Source 2 (Blue)"
$n2 label "Router"
$n3 label "Destination"

# Duplex links: n2->n3 is the narrow bottleneck link (1Mb, 300ms)
$ns duplex-link $n0 $n2 10Mb 300ms DropTail
$ns duplex-link $n1 $n2 10Mb 300ms DropTail
$ns duplex-link $n2 $n3 1Mb 300ms DropTail

# Queue limits: bottleneck link n2->n3 has a small queue of only 5 packets
$ns queue-limit $n0 $n2 10
$ns queue-limit $n1 $n2 10
$ns queue-limit $n2 $n3 5

# Setup Source 1: UDP agent (Class 1 = Red) + CBR traffic
set udp0 [new Agent/UDP]
$udp0 set class_ 1
$ns attach-agent $n0 $udp0
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005

# Setup Source 2: UDP agent (Class 2 = Blue) + CBR traffic
set udp1 [new Agent/UDP]
$udp1 set class_ 2
$ns attach-agent $n1 $udp1
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.005

# Setup Destination: Null sink at n3
set null3 [new Agent/Null]
$ns attach-agent $n3 $null3

# Connect sources to destination
$ns connect $udp0 $null3
$ns connect $udp1 $null3

# Finish procedure to close files and launch NAM
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam lab1.nam &
    exit 0
}

# Schedule simulation events
$ns at 0.1 "$cbr0 start"
$ns at 0.1 "$cbr1 start"
$ns at 10.0 "finish"

$ns run
