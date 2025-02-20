from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()

class Course(db.Model):
    id = db.Column(db.String(10), primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    professor_name = db.Column(db.String(100), nullable=False)
    students = db.relationship('Student', backref='course', lazy=True)

    def __repr__(self):
        return f'<Course {self.name}>'

class Student(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100), nullable=False)
    email = db.Column(db.String(100), nullable=False)
    course_id = db.Column(db.String(10), db.ForeignKey('course.id'))

    def __repr__(self):
        return f'<Student {self.name}>'