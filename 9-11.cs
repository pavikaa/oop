using System;
using System.Collections.Generic;
using System.Linq;

namespace Zadaci_9_11
{
    class Program
    {
        interface ITaxable
        {
            int getTaxPercentage();
            int getFullPrice();
            double getTaxPrice();
        }
        class Flour:ITaxable
        {
            public int TaxPercentage { get; private set; }
            public int QuantityKg { get; private set; }
            public int PricePerKg { get; private set; }
            public Flour(int taxPercentage, int quantityKg,int pricePerKg)
            {
                TaxPercentage = taxPercentage;QuantityKg = quantityKg;PricePerKg = pricePerKg;
            }
            public int getTaxPercentage()
            {
                return TaxPercentage;
            }
            public int getFullPrice()
            {
                int price = PricePerKg * QuantityKg;
                return price;
            }
            public double getTaxPrice()
            {
                double taxPrice = (TaxPercentage / 100) * PricePerKg * QuantityKg;
                return taxPrice;
            }
        }
        static int calculatePrice(List<ITaxable> list)
        {
            int priceSum=0;
            List<ITaxable> sortedList = list.OrderByDescending(o => o.getFullPrice()).ToList();
            for (int i = 0; i < sortedList.Count / 10; i++)
                priceSum += sortedList[i].getFullPrice();
            return priceSum;
        }
    static void Main(string[] args)
        {
            int n = 100;
            Random random=new Random();
            List<ITaxable> list = new List<ITaxable>();
            for (int i = 0; i < n; i++)
                list.Add(new Flour(random.Next(1, 100), random.Next(1, 10), random.Next(1, 10)));
            Console.WriteLine(calculatePrice(list));
        }
    }
}
