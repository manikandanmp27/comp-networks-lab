set ns [new Simulator]

# Open trace file and NAM animation file
set tf [open lab2.tr w]
$ns trace-all $tf
set nf [open lab2.nam w]
$ns namtrace-all $nf

# Create 4 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Colors: 1 = Red (TCP), 2 = Blue (UDP)
$ns color 1 "red"
$ns color 2 "blue"

# Labels for NAM
$n0 label "source/TCP"
$n1 label "source/UDP"
$n2 label "Router"
$n3 label "destination"

# Duplex links between nodes
$ns duplex-link $n0 $n2 100Mb 1ms DropTail
$ns duplex-link $n1 $n2 100Mb 1ms DropTail
$ns duplex-link $n2 $n3 100Mb 1ms DropTail

# --- TCP Setup on n0 with FTP application ---
set tcp0 [new Agent/TCP]
$tcp0 set class_ 1
$ns attach-agent $n0 $tcp0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3
$ns connect $tcp0 $sink3

# --- UDP Setup on n1 with CBR application ---
set udp1 [new Agent/UDP]
$udp1 set class_ 2
$ns attach-agent $n1 $udp1

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set packetSize_ 500
$cbr1 set interval_ 0.001

set null3 [new Agent/Null]
$ns attach-agent $n3 $null3
$ns connect $udp1 $null3

# Finish procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam lab2.nam &
    exit 0
}

# Schedule simulation events
$ns at 0.1 "$cbr1 start"
$ns at 0.2 "$ftp0 start"
$ns at 5.0 "finish"

$ns run
