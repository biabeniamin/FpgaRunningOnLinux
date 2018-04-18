import face_recognition
import cv2
import datetime
#image = face_recognition.load_image_file("biden.jpg")
#cap = cv2.VideoCapture(0)
#ret, img = cap.read()
a = datetime.datetime.now()
print("starting loading models")

# Load a sample picture and learn how to recognize it.
obama_image = face_recognition.load_image_file("test2.jpg")
obama_face_encoding = face_recognition.face_encodings(obama_image)[0]


# Create arrays of known face encodings and their names
known_face_encodings = [
    obama_face_encoding
]
def runFacial():
	fo2 = open("../functional/toProcess", "r")
	file = fo2.read()
	fo2.close()
	print("opening image")
	print(file)
	img = cv2.imread(file)
	print("image opened")
	b = datetime.datetime.now()
	print(b-a)


	small_frame = cv2.resize(img, (0, 0), fx=0.25, fy=0.25)


	fo = open("../functional/facialDone", "w")
	fo.write("0")
	fo.close()

	print("remove")
	rgb_small_frame = small_frame[:, :, ::-1]
	print("done remove")


	print("locations")
	face_locations = face_recognition.face_locations(rgb_small_frame)
	print("locations done")
	b = datetime.datetime.now()
	print(b-a)

	print("landmarks")
	face_encodings = face_recognition.face_encodings(rgb_small_frame)
	print("landmarks done")
	b = datetime.datetime.now()
	print(b-a)

	if len(face_encodings) > 0:
		print("comparing")
		matches = face_recognition.compare_faces(known_face_encodings, face_encodings[0])

		fo3 = open("../functional/result", "w")
		if True in matches:
			print("face detected")
			fo3.write("1")
		else:
			fo3.write("0")
		fo3.close()

		print(matches)
		print("comparing done")
		b = datetime.datetime.now()
		print(b-a)

	fo = open("../functional/facialDone", "w")
	fo.write("1")
	fo.close()
	fo = open("../functional/process", "w")
	process = fo.write("0")
	fo.close()
	#cv2.imwrite("test2.jpg", small_frame)
while 1==1:
	fo = open("../functional/process", "r")
	process = fo.read(1)
	fo.close()
	if process == "1":
		runFacial()
