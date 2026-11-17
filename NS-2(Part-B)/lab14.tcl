set ns [new Simulator]

# Open trace and NAM animation files
set tf [open lab14.tr w]
$ns trace-all $tf
set nf [open lab14.nam w]
$ns namtrace-all $nf

# Create 4 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Create an Ethernet LAN connecting all 4 nodes (802.3 CSMA/CD)
$ns make-lan "$n0 $n1 $n2 $n3" 10Mb 10ms LL Queue/DropTail Mac/802_3

# TCP Connection 1: n0 -> n3 with FTP
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3
$ns connect $tcp0 $sink3

# TCP Connection 2: n2 -> n1 with FTP
set tcp2 [new Agent/TCP]
$ns attach-agent $n2 $tcp2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp2 $sink1

# Trace Congestion Window (cwnd_) for both TCP connections
set file1 [open file1.tr w]
$tcp0 attach $file1
$tcp0 trace cwnd_

set file2 [open file2.tr w]
$tcp2 attach $file2
$tcp2 trace cwnd_

# Finish procedure
proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $tf
    close $nf
    exec nam lab14.nam &
    exit 0
}

# Schedule FTP transfers (overlapping active periods cause congestion)
$ns at 0.1 "$ftp0 start"
$ns at 1.5 "$ftp0 stop"
$ns at 2.0 "$ftp0 start"
$ns at 3.0 "$ftp0 stop"

$ns at 0.2 "$ftp2 start"
$ns at 2.0 "$ftp2 stop"
$ns at 2.5 "$ftp2 start"
$ns at 4.0 "$ftp2 stop"

$ns at 5.0 "finish"

$ns run
