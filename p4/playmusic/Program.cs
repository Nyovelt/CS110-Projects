using System;
using System.IO;
using System.IO.Ports;
using NAudio.Wave;
namespace ConsoleApp1
{
    class Program
    {
        static void PlayWave(string path)
        {
            using (var ms = File.OpenRead(path))
            using (var rdr = new WaveFileReader(ms))
            using (var wavStream = WaveFormatConversionStream.CreatePcmStream(rdr))
            using (var baStream = new BlockAlignReductionStream(wavStream))
            using (var waveOut = new WaveOut(WaveCallbackInfo.FunctionCallback()))
            {
                waveOut.Init(baStream);
                waveOut.Play();
                while (waveOut.PlaybackState == PlaybackState.Playing)
                {
                    System.Threading.Thread.Sleep(100);
                }
            }
        }



        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            SerialPort ComDevice = new SerialPort("COM4", 9600);
            
            while (true)
            {
                if (!ComDevice.IsOpen)
                    ComDevice.Open();
                string data =  ComDevice.ReadLine();
                if (data[0] == 'M')
                {
                    ComDevice.Close();
                    Console.WriteLine("Play Music");
                    PlayWave("./eva.wav");
                }
            }
            
        }   
    }
}
