using Animal;

var cat1 = new Cat(){
    Gender = "male",
    Age = 5,
    Color = "grey",
    Weight = 4.5,
};
var cat2 = new Cat(){
    Gender = "female",
    Age = 6,
    Color = "black",
    Weight = 4,
};
var tiger1 = new Tiger(){
    Gender = "male",
    Age = 8,
    Color = "grey",
    Weight = 15,
};
var tiger2 = new Tiger(){
    Gender = "female",
    Age = 10,
    Color = "black",
    Weight = 10,
};

Console.WriteLine(cat1);
Console.WriteLine(cat2);
Console.WriteLine(tiger1);
Console.WriteLine(tiger2);
Console.WriteLine(cat1.Equals(tiger1));
