using System;

namespace minimallibmaecsharp
{
  class MySequenceListener : maecsharp.NativeLabanSequenceSequenceListener
  {
    public virtual void on_sequence(ulong timestamp, maecsharp.LabanSequence sequence)
    {
        Console.WriteLine(""+timestamp);
    }
  }
}
