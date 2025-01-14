﻿using Microsoft.Win32;
using System;
using System.IO;
using System.Windows.Forms;

namespace ConsoleApplication
{
    public static class PrintHelper
    {

        public static void Exit(string Message = "")
        {
            printCentredLine(Message +"\n\n");
            printCentredLine(line());
            System.Threading.Thread.Sleep(2000);
        }

        public static void loopExplanation()
        {
            // entscheide
            Console.Clear();
            Console.WriteLine(line());
            Console.WriteLine("\n");
            printCentredLine("AML-Engine Console Application");
            printCentredLine("AML-Engine Version 1.3.6");
            Console.WriteLine("\n");
            printCentredLine("What do you want to do?\n\n");
            printCentredLine("Type \"Validate\" or 1 to Validate an AML-File\n");
            printCentredLine("Type \"Compress\" or 2 to Compress Files to an existing AMLX-File\n");
            printCentredLine("Type \"Decompress\" or 3 to Decompress an existing AMLX-File\n");
            printCentredLine("Type \"Options\" or 4 to Edit the Configuration\n");
            printCentredLine("Type \"Quit\" or \"Exit\" or 5 to exit the Program\n");
            Console.WriteLine("\n");
            Console.WriteLine(line()+"\n");
        }

        public static void DeCompressor_Choosage(bool Compress = true)
        {
            Console.Clear();
            Console.WriteLine(line() + "\n\n");
            if (Compress)
                printCentredLine("Compress a Folder to an AMLX-File\n\n");
            else
                printCentredLine("De-Compress an AMLX-File to a Folder\n\n");
        }

        public static string GetFile(string Filename = "Any File" , string FileExtensions = "")
        {
            System.Windows.Forms.OpenFileDialog dialog = new System.Windows.Forms.OpenFileDialog
            {
                Multiselect = false,
                Title = "Open " + Filename,
            };
            if (!String.IsNullOrEmpty(FileExtensions))
                dialog.Filter = Filename + "|" + FileExtensions;
            if (dialog.ShowDialog() == DialogResult.OK && File.Exists(@dialog.FileName))
                return @dialog.FileName;
            else
                return null;
        }

        public static string GetDirectory()
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            if (dialog.ShowDialog() == DialogResult.OK && Directory.Exists(@dialog.SelectedPath) && File.GetAttributes(@dialog.SelectedPath).HasFlag(FileAttributes.Directory))
                return @dialog.SelectedPath;
            else
                return null;
        }

        public static void println(string message, ConsoleColor color)
        {
            ConsoleColor defaultColor = Console.ForegroundColor;

            Console.ForegroundColor = color;

            printCentredLine(message);

            Console.ForegroundColor = defaultColor;
        }

        public static string line()
        {
            var x = "";
            for (int i = 0; i < Console.WindowWidth; i++)
            {
                x += "_";
            }


            return x;
        }

        public static void printOptions(bool AutoRepair, bool PrintAllVal)
        {
            Console.Clear();
            Console.WriteLine(line());
            Console.WriteLine("\n");
            printCentredLine("Available Options to configure this Program: \n\n");
            printCentredLine("AutoRepair: Automatically repairs all Issues found while Validating.  Current Value: "+AutoRepair.ToString()+"\n");
            printCentredLine("PrintAllVal: Prints all found Elements to the Console while Validating.  Current Value: " + PrintAllVal.ToString() + "\n\n");
            printCentredLine("Which Config do you want to Change?\n\n");
            printCentredLine("Type Exit, Quit or just press Enter to go back to Menu\n");
            Console.WriteLine("\n");
            Console.WriteLine(line() + "\n");
        }

        public static void printOptionAutoRepair(bool CurrentValue)
        {
            Console.Clear();
            Console.WriteLine(line());
            Console.WriteLine("\n");
            printCentredLine("What should be the new Value?\n");
            printCentredLine("Current Value : " + CurrentValue.ToString() + "\n\n");
            printCentredLine("Possible Values: \n");
            printCentredLine(" - false (default): The Validator asks before each repair, if the User wants to Repair this Issue\n");
            printCentredLine(" - true: The Validator automatically repairs all Issues found\n");
            Console.WriteLine("\n");
            Console.WriteLine(line() + "\n");
        }

        public static void printOptionPrintAllVal(bool CurrentValue)
        {
            Console.Clear();
            printCentredLine("What should be the new Value?\n");
            printCentredLine("Current Value : " + CurrentValue.ToString() + "\n\n");
            printCentredLine("Possible Values: \n");
            printCentredLine(" - false (default): The Validator does not print all Elements \n");
            printCentredLine(" - true: The Validator prints all found Elements \n");
            Console.WriteLine("\n");
            Console.WriteLine(line() + "\n");
        }

        public static void printCentredLine(string text)
        {
            Console.WriteLine(String.Format("{0," + ((Console.WindowWidth / 2) + (text.Length / 2)) + "}", text));
        }

        public static void SetRegistryKey(string KeyName, string Value)
        {
            RegistryKey MainKey = GetRegistry();
            MainKey.SetValue(KeyName, Value);
        }

        private static RegistryKey GetRegistry()
        {
            RegistryKey GlobalKey = Registry.CurrentUser.OpenSubKey("Software", true);
            RegistryKey MainKey = GlobalKey.OpenSubKey("ConsoleApplication", true);
            if (MainKey == null)
            {
                GlobalKey.CreateSubKey("ConsoleApplication");
                MainKey = GlobalKey.OpenSubKey("ConsoleApplication", true);
            }
            return MainKey;
        }

        public static string GetRegistryKey(string KeyName)
        {
            RegistryKey MainKey = GetRegistry();
            if (MainKey.GetValue(KeyName) == null)
                return null;
            else
                return MainKey.GetValue(KeyName).ToString();
        }
    }
}
