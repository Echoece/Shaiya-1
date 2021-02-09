//https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3596037-release-call-psmagent-commands-via-sql.html
using System;
using System.Text;
using System.IO;
using System.Net.Sockets;

class Program
{
    static void Main(string[] argv)
    {
        byte[] buffer = new byte[512];
        Socket sender = null;

        try
        {
            sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            sender.Connect("127.0.0.1", 40900);

            var binary = new BinaryWriter(new MemoryStream());

            string service = "ps_game";
            string command = argv[0].ToString();

            binary.BaseStream.Position = 0;
            binary.Write((short)(command.Length + 262));
            binary.Write((short)(1281));
            binary.Write(Encoding.ASCII.GetBytes(service));
            binary.BaseStream.Position = 260;
            binary.Write((short)command.Length);
            binary.Write(Encoding.ASCII.GetBytes(command));

            byte[] packet = ((MemoryStream)binary.BaseStream).ToArray();
            sender.Send(packet);
            sender.Receive(buffer);
            sender.Shutdown(SocketShutdown.Both);
        }
        catch (SocketException e)
        {
            Console.Error.Write(e);
        }
        catch (Exception e)
        {
            Console.Error.Write(e);
        }
        finally
        {
            sender.Close();
        }
    }
}
