using JSONParser.Model;
using System;
using System.Collections.Generic;

namespace JSONParser
{
    class Program
    {
        static void Main(string[] args)
        {
            Parser jSONParser = new Parser();
            List<User> users = jSONParser.Parse("json.json");

            ShowStatistics(users);
        }

        static void ShowStatistics(List<User> users)
        {
            double averageAge = 0;
            double averageLatitude = 0;
            double averageLongitude = 0;
            foreach (var user in users)
            {
                averageAge += user.Age;
                averageLatitude += user.Latitude;
                averageLongitude += user.Longitude;
            }
            averageAge /= users.Count;
            averageLatitude /= users.Count;
            averageLongitude /= users.Count;

            Console.WriteLine($"Average Age: {averageAge}\nAverage Latitude: {averageLatitude}\n" +
                $"Average Longitude: {averageLongitude}\n");
        }
    }
}
