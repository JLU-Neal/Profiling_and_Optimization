/*
 * Copyright (c) 2014, Oracle America, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *  * Neither the name of Oracle nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

package uk.ac.ic.doc.spe;

import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.TimeUnit;
import java.util.stream.Stream;


import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.runner.Runner;
import org.openjdk.jmh.runner.RunnerException;
import org.openjdk.jmh.runner.options.Options;
import org.openjdk.jmh.runner.options.OptionsBuilder;
;
import tech.tablesaw.api.IntColumn;
import tech.tablesaw.api.StringColumn;

import tech.tablesaw.api.Table;

import tech.tablesaw.table.TableSliceGroup;

@BenchmarkMode(Mode.AverageTime)
@OutputTimeUnit(TimeUnit.NANOSECONDS)
@Warmup(iterations = 5, time = 1, timeUnit = TimeUnit.SECONDS)
@Measurement(iterations = 5, time = 1, timeUnit = TimeUnit.SECONDS)
@Fork(1)
@State(Scope.Benchmark)
public class MyBenchmark {
    static boolean offline = true;
    static Table input;

//    static double[] cuteness = {90.1, 84.3, 99.7};

    @Param({"1", "10", "100", "1000", "10000"})
    public int repeat;

    @Setup
    public void setUp(){
        try{
            //benchmarks should not depend on external data.
            System.out.println("Repeat param: " + repeat);
            Random random = new Random();

            int[] repeatedAnimals = new int[repeat];
            for(int i = 0 ; i < repeat; i++){
                repeatedAnimals[i] = random.nextInt();
            }
            System.out.println("Array Length: "+repeatedAnimals.length);

            input = Table.create("Cute Animals")
                    .addColumns(
                            IntColumn.create("Animal types", repeatedAnimals));


        }catch(Exception exception){
            System.out.println("Error " + exception.getMessage());
            exception.printStackTrace();
        }
    }


    public MyBenchmark(){
        
    }
    @Benchmark
    public void testMethod() {
        TableSliceGroup ret = input.splitOn("Animal types");
//        System.out.println("=====]====================");
//        System.out.println(ret.asTableList());
    }

    public static void main(String[] args) throws RunnerException {
        Options opt = new OptionsBuilder()
                .include(MyBenchmark.class.getSimpleName())
//                .param("arg", "41", "42") // Use this to selectively constrain/override parameters
                .build();

        new Runner(opt).run();
    }
}
