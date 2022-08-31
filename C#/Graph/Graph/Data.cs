using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Graph
{
    public class Data
    {
		public static  Object[][] MST_01 = {
			{0, 2, 2}, {0, 4, 7},
			{1, 2, 3}, {1, 5, 1}, {1, 6, 7},
			{2, 4, 4}, {2, 5, 3}, {2, 6, 6},
			{3, 7, 9},
			{4, 6, 8},
			{5, 6, 4}, {5, 7, 5}
		};
	
		public static  Object[][] MST_02 = {
			{"A", "B", 17}, {"A", "F", 1}, {"A", "E", 16},
			{"B", "C", 6}, {"B", "D", 5}, {"B", "F", 11},
			{"C", "D", 10}, 
			{"D", "E", 4}, {"D", "F", 14},
			{"E", "F", 33}
		};
    }
}
