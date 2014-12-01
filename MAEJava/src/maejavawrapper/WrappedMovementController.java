package maejavawrapper;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

import maejava.BoneVector;
import maejava.ColumnDefinitionVector;
import maejava.ETimeUnit;
import maejava.FlMovementController;
import maejava.FlSkeleton;
import maejava.GeneralPose;
import maejava.GeneralSkeleton;
import maejava.LabanSequence;
import maejava.LabanSequenceGenerator;
import maejava.LabanSequenceVector;
import maejava.StringVector;

public class WrappedMovementController extends FlMovementController {

	List<IJRecognitionListener> recognitionListeners = new ArrayList<IJRecognitionListener>();
	List<IJSequenceListener> sequenceListeners = new ArrayList<IJSequenceListener>();
	List<IJPoseListener> poseListeners = new ArrayList<IJPoseListener>();

	public WrappedMovementController(long pose_buffer_size, double framerate,
			boolean debug) {
		super(pose_buffer_size, framerate, debug);
	}

	public WrappedMovementController(long pose_buffer_size, double framerate) {
		super(pose_buffer_size, framerate);
	}

	public WrappedMovementController(long pose_buffer_size) {
		super(pose_buffer_size);
	}

	public WrappedMovementController() {
		super();
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration, ETimeUnit time_unit,
			double framerate, boolean debug) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration, time_unit, framerate, debug);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration, ETimeUnit time_unit,
			double framerate) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration, time_unit, framerate);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration, ETimeUnit time_unit) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration, time_unit);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions, long pose_buffer_size,
			long beats_per_measure) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions, long pose_buffer_size) {
		super(body_parts, column_definitions, pose_buffer_size);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions) {
		super(body_parts, column_definitions);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions,
			LabanSequenceGenerator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration, ETimeUnit time_unit,
			double framerate, boolean debug) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration, time_unit,
				framerate, debug);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions,
			LabanSequenceGenerator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration, ETimeUnit time_unit,
			double framerate) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration, time_unit,
				framerate);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions,
			LabanSequenceGenerator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration, ETimeUnit time_unit) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration, time_unit);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions,
			LabanSequenceGenerator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions,
			LabanSequenceGenerator sequence_generator, long pose_buffer_size,
			long beats_per_measure) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions,
			LabanSequenceGenerator sequence_generator, long pose_buffer_size) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size);
	}

	public WrappedMovementController(BoneVector body_parts,
			ColumnDefinitionVector column_definitions,
			LabanSequenceGenerator sequence_generator) {
		super(body_parts, column_definitions, sequence_generator);
	}

	@Override
	public void nextFrame(BigInteger timestamp, GeneralSkeleton skeleton) {
		super.nextFrame(timestamp, skeleton);

		notifySequenceListeners(timestamp, getCurrentSequence());
		notifyRecognitionListeners(timestamp, getCurrentRecognition());
		notifyPoseListeners(timestamp, getCurrentPose());
	}

	@Override
	public void nextFrame(BigInteger timestamp, FlSkeleton skeleton) {
		super.nextFrame(timestamp, skeleton);

		notifySequenceListeners(timestamp, getCurrentSequence());
		notifyRecognitionListeners(timestamp, getCurrentRecognition());
		notifyPoseListeners(timestamp, getCurrentPose());
	}

	public void addListener(IJRecognitionListener listener) {
		recognitionListeners.add(listener);
	}

	public boolean removeListener(IJRecognitionListener listener) {
		return recognitionListeners.remove(listener);
	}

	public void addListener(IJSequenceListener listener) {
		sequenceListeners.add(listener);
	}

	public boolean removeListener(IJSequenceListener listener) {
		return sequenceListeners.remove(listener);
	}

	public void addListener(IJPoseListener listener) {
		poseListeners.add(listener);
	}

	public boolean removeListener(IJPoseListener listener) {
		return poseListeners.remove(listener);
	}

	public void notifySequenceListeners(BigInteger timestamp, LabanSequence sequence) {
		for (IJSequenceListener listener : sequenceListeners) {
			listener.onSequence(timestamp, sequence);
		}
	}

	public void notifyRecognitionListeners(BigInteger timestamp,
			LabanSequenceVector sequences) {
		StringVector sequenceTitles = new StringVector();
		for (int i = 0; i < sequences.size(); i++) {
			sequenceTitles.pushBack(sequences.get(i).getTitle());
		}

		for (IJRecognitionListener listener : recognitionListeners) {
			listener.onRecognition(timestamp, sequences);
			listener.onRecognition(timestamp, sequenceTitles);
		}
	}

	public void notifyPoseListeners(BigInteger timestamp, GeneralPose pose) {
		for (IJPoseListener listener : poseListeners) {
			listener.onPose(timestamp, pose);
		}
	}

}
