package maejavawrapper;

import java.util.ArrayList;
import java.util.List;

import maejava.bone_vector;
import maejava.coldef_vector;
import maejava.e_time_unit;
import maejava.fl_movement_controller;
import maejava.fl_skeleton;
import maejava.general_pose;
import maejava.general_skeleton;
import maejava.laban_sequence;
import maejava.laban_sequence_generator;
import maejava.laban_sequence_vector;
import maejava.string_vector;

public class WrappedMovementController extends fl_movement_controller {

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

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration, e_time_unit time_unit,
			double framerate, boolean debug) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration, time_unit, framerate, debug);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration, e_time_unit time_unit,
			double framerate) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration, time_unit, framerate);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration, e_time_unit time_unit) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration, time_unit);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions, long pose_buffer_size,
			long beats_per_measure, long beat_duration) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure, beat_duration);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions, long pose_buffer_size,
			long beats_per_measure) {
		super(body_parts, column_definitions, pose_buffer_size,
				beats_per_measure);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions, long pose_buffer_size) {
		super(body_parts, column_definitions, pose_buffer_size);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions) {
		super(body_parts, column_definitions);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions,
			laban_sequence_generator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration, e_time_unit time_unit,
			double framerate, boolean debug) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration, time_unit,
				framerate, debug);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions,
			laban_sequence_generator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration, e_time_unit time_unit,
			double framerate) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration, time_unit,
				framerate);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions,
			laban_sequence_generator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration, e_time_unit time_unit) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration, time_unit);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions,
			laban_sequence_generator sequence_generator, long pose_buffer_size,
			long beats_per_measure, long beat_duration) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure, beat_duration);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions,
			laban_sequence_generator sequence_generator, long pose_buffer_size,
			long beats_per_measure) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size, beats_per_measure);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions,
			laban_sequence_generator sequence_generator, long pose_buffer_size) {
		super(body_parts, column_definitions, sequence_generator,
				pose_buffer_size);
	}

	public WrappedMovementController(bone_vector body_parts,
			coldef_vector column_definitions,
			laban_sequence_generator sequence_generator) {
		super(body_parts, column_definitions, sequence_generator);
	}

	@Override
	public void next_frame(int timestamp, general_skeleton skeleton) {
		super.next_frame(timestamp, skeleton);

		notifySequenceListeners(timestamp, get_current_sequence());
		notifyRecognitionListeners(timestamp, get_current_recognition());
		notifyPoseListeners(timestamp, get_current_pose());
	}

	@Override
	public void next_frame(int timestamp, fl_skeleton skeleton) {
		super.next_frame(timestamp, skeleton);

		notifySequenceListeners(timestamp, get_current_sequence());
		notifyRecognitionListeners(timestamp, get_current_recognition());
		notifyPoseListeners(timestamp, get_current_pose());
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

	public void notifySequenceListeners(int timestamp, laban_sequence sequence) {
		for (IJSequenceListener listener : sequenceListeners) {
			listener.onSequence(timestamp, sequence);
		}
	}

	public void notifyRecognitionListeners(int timestamp,
			laban_sequence_vector sequences) {
		string_vector sequenceTitles = new string_vector();
		for (int i = 0; i < sequences.size(); i++) {
			sequenceTitles.add(sequences.get(i).get_title());
		}

		for (IJRecognitionListener listener : recognitionListeners) {
			listener.onRecognition(timestamp, sequences);
			listener.onRecognition(timestamp, sequenceTitles);
		}
	}

	public void notifyPoseListeners(int timestamp, general_pose pose) {
		for (IJPoseListener listener : poseListeners) {
			listener.onPose(timestamp, pose);
		}
	}

}
