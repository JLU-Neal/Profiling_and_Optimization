package uk.ac.ic.doc.spe.covidsaw;

import tech.tablesaw.analytic.AnalyticQuery;
import tech.tablesaw.api.DateColumn;
import tech.tablesaw.api.IntColumn;
import tech.tablesaw.api.Table;
import tech.tablesaw.io.csv.CsvReadOptions;

import java.net.URL;
import java.time.LocalDate;

import static tech.tablesaw.aggregate.AggregateFunctions.max;

public class App {
    private static boolean offline = true; // set to false to live-download dataset

    public static void main(String[] args) {
        try {

            Table input = offline ? Table.read().csv("owid-covid-data.csv")
                    : Table.read().usingOptions(CsvReadOptions.builder(new URL(
                            "https://github.com/owid/covid-19-data/blob/master/public/data/owid-covid-data.csv?raw=true")));

            input.addColumns(input
                             .numberColumn("new_cases")
                             .multiply(1000000)
                             .divide(input.numberColumn("population"))
                             .roundInt()
                             .setName("new_cases / population"))
                .retainColumns("iso_code", "date", "new_cases", "population", "new_cases / population");

            Table inputWithSmoothedCaseload = input
                .where(input.numberColumn("population").isGreaterThan(1000000));

            LocalDate[] dates = {};
            DateColumn.create("duh", dates);
            IntColumn a;
            AnalyticQuery
                .query()
                .from(inputWithSmoothedCaseload)
                .partitionBy("iso_code")
                .orderBy("date")
                .rowsBetween()
                .preceding(3)
                .andFollowing(3)
                .sum("new_cases / population")
                .as("smoothed")
                .executeInPlace();
            
            Table highestCaseloadByDay = inputWithSmoothedCaseload
                .where(inputWithSmoothedCaseload.column("smoothed").isNotMissing())
                .joinOn("date")
                .inner(true, inputWithSmoothedCaseload)
                .summarize("smoothed", max).by("date");
            highestCaseloadByDay = highestCaseloadByDay.where(highestCaseloadByDay.numberColumn("Max [smoothed]").isGreaterThan(0));
            highestCaseloadByDay.column("Max [smoothed]").setName("smoothed");

            Table result = highestCaseloadByDay
                .joinOn("smoothed", "date")
                .inner(true, inputWithSmoothedCaseload)
                .retainColumns("date", "iso_code", "smoothed")
                .sortAscendingOn("date");

            System.out.println(result);
        } catch (Throwable e) {
            System.out.println("Error " + e.getMessage());
            e.printStackTrace();
        }

    }
}
