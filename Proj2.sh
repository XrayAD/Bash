#!/bin/bash

for testInput in *.std; do
   name=${testInput%.in}
   echo "Stdin no flags"
   ./a.out <$name> $name.out
   swc.sh <$name> $name.expect
   diff $name.out $name.expect
done
echo "One file, no flags"
./a.out herro.txt >herro.out
swc.sh herro.txt >herro.expect
diff herro.out herro.expect

echo "One file, no flags"
./a.out simp.std >simp.out
swc.sh simp.std >simp.expect
diff simp.out simp.expect

echo "Multiple files, no flags"
./a.out herro.txt simp.std >two.out
swc.sh herro.txt simp.std >two.expect
diff two.out two.expect

echo "One binary file, no flags"
./a.out another.bin >another.out
swc.sh another.bin >another.expect
diff another.out another.expect

echo "one flag, one file"
declare -a arr=("-l" "-c" "-w")
for i in "${arr[@]}"; do
   ./a.out $i herro.txt >$iher.out
   swc.sh $i herro.txt >$iher.expect
   diff $iher.out $iher.expect
done
echo "one flag, stdin"
for i in "${arr[@]}"; do
   ./a.out $i <herro.txt >$iherstd.out
   swc.sh $i <herro.txt >$iherstd.expect
   diff $iherstd.out $iherstd.expect
done

echo "unique combo of two flags, one file"
declare -a arg=("-l -c" "-l -w" "-w -c" "-w -l" "-l -l" "-c -c" "-c -w" "-c -l")
for i in "${arg[@]}"; do
   ./a.out $i herro.txt >$iher.out
   swc.sh $i herro.txt >$iher.expect
   diff $iher.out $iher.expect
done

echo "unique combo of two flags, stdin"
for i in "${arg[@]}"; do
   ./a.out $i <herro.txt >$iher.out
   swc.sh $i <herro.txt >$iher.expect
   diff $iher.out $iher.expect
done

echo "tests after files"
for i in "${arg[@]}"; do
   ./a.out  herro.txt $i >$iher.out
   swc.sh  herro.txt $i >$iher.expect
   diff $iher.out $iher.expect
done

echo "tests in files"
for i in "${arg[@]}"; do
   ./a.out  herro.txt $i file.bin>$iher.out
   swc.sh  herro.txt $i file.bin>$iher.expect
   diff $iher.out $iher.expect
done
declare -a arm=("-l -w -c" "-l -c -w" "-c -l -w" "-c -w -l" "-w -l -c" "-w -c -l")
echo "three flags file"
for i in "${arm[@]}"; do
   ./a.out simp.txt $i >simp.out
   swc.sh $i simp.txt >simp.expect
   diff simp.out simp.expect
done

echo "three flags stdin"
for i in "${arm[@]}"; do
   ./a.out <simp.txt $i >simp.out
   swc.sh $i <simp.txt >simp.expect
   diff simp.out simp.expect
done

echo "bad flags, no good flags"
./a.out -x herro.txt 1>hm.out 2>hm.ero
swc.sh -x herro.txt 1>hm.expect 2>hm.err
diff hm.out hm.expect
diff hm.ero hm.err

echo "bad flags and good flags"
./a.out -x -c -l herro.txt 1>hmm.out 2>hmm.ero
swc.sh herro.txt -c -l -x 1>hmm.expect 2>hmm.err
diff hmm.out hmm.expect
diff hmm.ero hmm.err

echo "duplicate flags file"
./a.out -l -l -l -l -l -l herro.txt -l -l >ok.out
swc.sh -l herro.txt -l >ok.expect
diff ok.out ok.expect
echo "duplicate flags stdin"
echo "duplicate flags file"
./a.out -l -l -l -l -l -l <herro.txt >ok.out
swc.sh -l <herro.txt >ok.expect
diff ok.out ok.expect

echo "nonexistant file"
./a.out bam 1>bam.out 2>bam.err
swc.sh bam 1>bam.expect 2>bam.ero
diff bam.out bam.expect
diff bam.err bam.ero

echo "unreadable file"
./a.out cantread.txt 1>bam.out 2>bam.err
swc.sh cantread.txt 1>bam.expect 2>bam.ero
diff bam.out bam.expect
diff bam.err bam.ero


echo "mix of good and bad inputs"
./a.out cantread.txt herro.txt -l -c binary-file bam 1>mix.out 2>mix.ero
swc.sh cantread.txt herro.txt -l -c binary-file bam 1>mix.expect 2>mix.err
diff mix.out mix.expect
diff mix.ero mix.err

echo "hyphen file"
./a.out binary-file > bin.sauce
swc.sh binary-file >bin.expect
diff bin.sauce bin.expect
