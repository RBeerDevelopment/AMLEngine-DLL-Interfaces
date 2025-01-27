﻿using Aml.Engine.CAEX;
using CommandLine;
using System;
using System.Collections.Generic;
using System.IO;

/**
 * Ablauf Diagramme:
 * https://raw.githubusercontent.com/RBeerDevelopment/TINF18C_Team_4_AMLEngine-DLL-Interface/master/PROJECT/Pictures/Diagrams/aktivitaetsdiagrammValidation.png
 * https://raw.githubusercontent.com/RBeerDevelopment/TINF18C_Team_4_AMLEngine-DLL-Interface/master/PROJECT/Pictures/Diagrams/aktivitaetsdiagrammPacking.png
 *
 * Dokument:
 * https://github.com/RBeerDevelopment/TINF18C_Team_4_AMLEngine-DLL-Interface/wiki/System-Requirements

 * Willkommen
 * SCHLEIFE: 
 *      Entscheiden zwischen 
 *           1. File-Validation und 
 *           2. De / Compressor
 *           3. EXIT
 *           
 *          1. File Validation
 *              GIB Pfad zu Datei ein
 *              -> Ergebniss wird aus gegeben
 *          
 *          2. Entscheiden zwischen 
 *                  1. Packen und
 *                  2. Entpacken
 *              
 *                  1. Packen:
 *                      gib Dateipfad ein zu AMl Datei
 *                      gib Verzeichnisspfad ein / für Speicherort
 *                  
 *                  2. Entpacken
 *                      gib Dateipfad ein zu AMLX (zip) Datei
 *                      gib Verzeichnisspfad ein / für Speicherort
 *                      
 *          3. EXIT
 *              durchbricht Loop
 */

namespace ConsoleApplication
{
    public class Program
    {
        [STAThread]
        public static void Main(string[] args)
        {
            try
            {
                string path = "";
                bool ContinueMainMenu = true;
                Options CurrentOptions = new Options();

                Validator ValidatorInstance = new Validator();
                // First try Execution with Parameters
                if (!IsNullOrEmpty(args))
                {
                    Parser.Default.ParseArguments<CommandLineOptions>(args)
                        .WithParsed(options =>
                        {
                            if (!String.IsNullOrEmpty(options.path))
                            {
                                if (!File.Exists(@options.path) || !(Path.GetExtension(@options.path).ToUpper() == ".AML"))
                                {
                                    // Path is not Valid or File is not an AML File
                                    PrintHelper.Exit("Please provide a valid path");
                                    ContinueMainMenu = false;
                                }
                                else if (!options.validate && !options.compress)
                                {
                                    // No Defined Parameter given
                                    PrintHelper.Exit("Please provide either the Parameter --validate for validating or --compress for compressing");
                                    ContinueMainMenu = false;
                                }
                                else if (options.validate && options.compress)
                                {
                                    // Too much Parameters given
                                    PrintHelper.Exit("Please just provide just --validate or --compress");
                                    ContinueMainMenu = false;
                                }
                                else
                                {
                                    // Parameters are Valid
                                    if (options.validate)
                                    {
                                        path = options.path;
                                        //validate file
                                        Console.Clear();
                                        CAEXDocument CDokument = LoadFile(ref path);
                                        Console.WriteLine(path);
                                        if (CDokument != null)
                                            ValidatorInstance.validate(CDokument, path, ref CurrentOptions);
                                        // Empty path for next Validation
                                        path = "";
                                    }
                                    else if (options.compress)
                                    {
                                        AMLXCompress(@options.path);
                                    }
                                }
                            }
                        });
                }
                else
                {
                    while (ContinueMainMenu)
                    {
                        PrintHelper.loopExplanation();

                        switch (Console.ReadLine().ToUpper())
                        {
                            case "VALIDATE":
                            case "1":
                                //validate file
                                Console.Clear();
                                CAEXDocument CDokument = LoadFile(ref path);
                                Console.WriteLine(path);
                                if (CDokument != null)
                                    ValidatorInstance.validate(CDokument, path, ref CurrentOptions);
                                // Empty path for next Validation
                                path = "";
                                break;
                            case "COMPRESS":
                            case "2":
                                AMLXCompress();
                                break;
                            case "DECOMPRESS":
                            case "3":
                                AMLXDeCompress();
                                break;
                            case "OPTIONS":
                            case "4":
                                EditOptions(ref CurrentOptions);
                                break;
                            case "EXIT":
                            case "QUIT":
                            case "5":
                                ContinueMainMenu = false;
                                break;


                            default:
                                Console.WriteLine("Invalid Input \n");
                                continue;
                        }

                    }

                    // Wait for 3 Seconds before closing, so the User can see the message
                    PrintHelper.Exit("Thanks for using this Console Application. Exiting... ");
                }
                CurrentOptions.SaveOptions();
            }
            catch(Exception e)
            {
                Console.WriteLine("Exception: " + e.ToString());
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine("SCHWERER AUSNAHMEFEHLER. PROGRAMM WIRD IN 20 SEKUNDEN BEENDET");
                System.Threading.Thread.Sleep(20000);
            }
        }

        private static void AMLXCompress(string sourceAMLFile = "")
        {
            string target, newFile;
            bool AnotherFile;
            List<string> FilesToAdd = new List<string>();
            PrintHelper.DeCompressor_Choosage(true);

            if (String.IsNullOrEmpty(sourceAMLFile))
            {
                PrintHelper.printCentredLine("What is your Input AML-File?\n\n");
                sourceAMLFile = PrintHelper.GetFile("AML-File", "*.AML");
            }
            // User Aborted Compress
            if (String.IsNullOrEmpty(sourceAMLFile))
                return;

            PrintHelper.printCentredLine("Do you want to add another File?(Yes/No)\n\n");
            AnotherFile = Console.ReadLine().ToUpper() == "YES";
            while(AnotherFile)
            {
                newFile = PrintHelper.GetFile();
                if (!String.IsNullOrEmpty(newFile))
                {
                    if (FilesToAdd.Contains(newFile) || newFile == sourceAMLFile)
                        PrintHelper.printCentredLine("You already added this File");
                    else
                        FilesToAdd.Add(newFile);
                    PrintHelper.printCentredLine("Do you want to add more Files?(Yes/No)\n\n");
                    AnotherFile = Console.ReadLine().ToUpper() == "YES";
                }
                else
                    break;
            }

            PrintHelper.printCentredLine("Where do you want to save the Output?\n\n\n");
            target = PrintHelper.GetDirectory();
            if (String.IsNullOrEmpty(target))
                return;
            DeCompressor.Compress(sourceAMLFile, target, FilesToAdd);
        }

        private static void AMLXDeCompress()
        {
            string src, target;
            PrintHelper.DeCompressor_Choosage(false);

            PrintHelper.printCentredLine("What is your Input?\n\n");
            src = PrintHelper.GetFile("AMLX-File", "*.AMLX");
            if (String.IsNullOrEmpty(src) || (Path.GetExtension(src).ToUpper() != ".AMLX"))
                return;

            PrintHelper.printCentredLine("Where do you want to save the Output?\n\n");
            target = PrintHelper.GetDirectory();
            if (String.IsNullOrEmpty(target))
                return;
            DeCompressor.DeCompress(src, target);
        }

        private static CAEXDocument LoadFile(ref string AMLFile)
        {
            PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
            if (String.IsNullOrEmpty(AMLFile))
            {
                // Ask for File
                PrintHelper.printCentredLine("Which File do you want to validate?\n");
                AMLFile = PrintHelper.GetFile("AML-File", "*.AML");
            }
            // look up input is actual file
            if (String.IsNullOrEmpty(AMLFile))
                return null;
            else
                return CAEXDocument.LoadFromFile(AMLFile);  

        }
        private static void EditOptions(ref Options CurrentOptions)
        {
            bool Continue = true;
            bool ExceptionHappend = false;
            do
            {
                PrintHelper.printOptions(CurrentOptions.AutoRepair,CurrentOptions.PrintAllVal);
                string SelectedOption = Console.ReadLine().ToUpper();
                switch (SelectedOption)
                {
                    case "":
                    case "EXIT":
                    case "QUIT":
                        Continue = false;
                        break;
                    case "AUTOREPAIR":
                        PrintHelper.printOptionAutoRepair(CurrentOptions.AutoRepair);
                        try
                        {
                            CurrentOptions.AutoRepair = bool.Parse(Console.ReadLine());
                        }
                        catch (Exception)
                        {
                            Console.Clear();
                            PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                            PrintHelper.println("Invalid Value. Did not Change Config\n\n", ConsoleColor.Red);
                            ExceptionHappend = true;
                        }
                        if(!ExceptionHappend)
                        {
                            Console.Clear();
                            PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                        }
                        Console.WriteLine("Do you want to Edit another Value? (Yes/No)\n");
                        PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                        if (Console.ReadLine().ToUpper() == "NO")
                            Continue = false;
                        break;
                    case "PRINTALLVAL":
                        PrintHelper.printOptionPrintAllVal(CurrentOptions.PrintAllVal);
                        try
                        {
                            CurrentOptions.PrintAllVal = bool.Parse(Console.ReadLine());
                        }
                        catch (Exception)
                        {
                            Console.Clear();
                            PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                            PrintHelper.println("Invalid Value. Did not Change Config\n\n", ConsoleColor.Red);
                            ExceptionHappend = true;
                        }
                        if (!ExceptionHappend)
                        {
                            Console.Clear();
                            PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                        }
                        Console.WriteLine("Do you want to Edit another Value? (Yes/No)\n");
                        PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                        if (Console.ReadLine().ToUpper() == "NO")
                            Continue = false;
                        break;
                    default:
                        Console.Clear();
                        PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                        PrintHelper.printCentredLine("This Option does not Exist.\n\n");
                        PrintHelper.printCentredLine("Do you want to try again? (Yes/No)\n\n");
                        PrintHelper.printCentredLine(PrintHelper.line() + "\n\n");
                        if (Console.ReadLine().ToUpper() == "NO")
                            Continue = false;
                        break;
                }
            } while (Continue);
            Console.Clear();
            PrintHelper.Exit("Redirecting to Main Menu");
        }

        private static bool IsNullOrEmpty(String[] array)
        {
            return (array == null || array.Length == 0);
        }

        private class CommandLineOptions
        {
            // Path must be given expicitly or it doesnt accept a uppercase Letter
            [Option(HelpText = "Insert path of your AML-File that you want to load", Default = null, Required = false)]
            public string path { get; set; }

            [Option(HelpText = "Validate the File in path", Default = false, Required = false)]
            public bool validate { get; set; }

            [Option(HelpText = "Compress the File in path", Default = false, Required = false)]
            public bool compress { get; set; }
        }
    }
}
