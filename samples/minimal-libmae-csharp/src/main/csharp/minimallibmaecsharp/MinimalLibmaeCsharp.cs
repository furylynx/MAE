using System;
using maecsharp;

namespace minimallibmaecsharp
{
    class MinimalLibmaeCsharp
    {
        static void Main(string[] args)
        {
            BoneVector bones = Bone.default_hand_bones(false);

            foreach(Bone bone in bones)
            {
                Console.WriteLine(bone.get_name());
            }
            
        }
    }
}
