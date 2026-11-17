set ns [new Simulator]

# Open trace and NAM animation files
set tf [open lab5.tr w]
$ns trace-all $tf
set nf [open lab5.nam w]
$ns namtrace-all $nf

# Colors & Node Labels
$ns color 1 "red"

# Create 7 nodes (n0-n3 in LAN1, n4-n6 in LAN2)
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

$n1 label "Source (n1)"
$n3 label "Gateway 1 (n3)"
$n5 label "Destination (n5)"
$n6 label "Gateway 2 (n6)"

# Create LAN 1 and LAN 2
$ns make-lan "$n0 $n1 $n2 $n3" 10Mb 10ms LL Queue/DropTail Mac/802_3
$ns make-lan "$n4 $n5 $n6" 10Mb 10ms LL Queue/DropTail Mac/802_3

# Connect the two LANs via a point-to-point link between gateways
$ns duplex-link $n3 $n6 100Mb 10ms DropTail

# UDP agent on n1 and Null sink on n5
set udp1 [new Agent/UDP]
$udp1 set class_ 1
$ns attach-agent $n1 $udp1

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set packetSize_ 1000
$cbr1 set interval_ 0.0001

set null5 [new Agent/Null]
$ns attach-agent $n5 $null5
$ns connect $udp1 $null5

# Add an Error Model on the gateway link between n3 and n6
set err [new ErrorModel]
$ns lossmodel $err $n3 $n6
$err set rate_ 0.2

# Finish procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam lab5.nam &
    exit 0
}

# Schedule events
$ns at 0.1 "$cbr1 start"
$ns at 5.0 "finish"

$ns run
