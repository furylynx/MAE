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

            MySequenceListener sequenceListener = new MySequenceListener();
            FlMovementController mc = new FlMovementController();
            mc.add_listener(sequenceListener);

            BvhController bvhController = new BvhController();
            BvhData data = bvhController.read_bvh_file("../tutorial-bvhreader/file.bvh", BvhSpec.default_spec());

            ulong timestamp = 0;
            foreach(GeneralSkeleton skel in data.get_skeleton_data())
            {
                Console.WriteLine("it "+timestamp);
                mc.next_frame(timestamp, skel);
                timestamp++;
            }

        }
    }
}
