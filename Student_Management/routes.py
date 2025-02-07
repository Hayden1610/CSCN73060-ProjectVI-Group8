from flask import render_template, request, redirect, flash
from models import Course, db

def init_app(app):
    @app.route('/')
    def home():
        courses = Course.query.all()
        return render_template('index.html', courses=courses)

    @app.route('/edit_course', methods=['GET', 'POST'])
    def edit_course():
        if request.method == 'POST':
            action = request.form.get('action')
            course_id = request.form.get('course_id')
            course_name = request.form.get('course_name')
            professor_name = request.form.get('professor_name')

            if action == 'add':
                # Make sure enter cant be empty
                if not course_id or not course_name or not professor_name:
                    flash("All fields are required!", "danger")
                else:
                    # Check if Same Course ID
                    existing_course = Course.query.get(course_id)
                    if existing_course:
                        flash("Course ID already exists!", "danger")
                    else:
                        # Add New Course
                        new_course = Course(id=course_id, name=course_name, professor_name=professor_name)
                        db.session.add(new_course)
                        db.session.commit()
                        flash("Course added successfully!", "success")
            elif action == 'update':
                # Update Course Information
                course = Course.query.get(course_id)
                if course:
                    course.name = course_name
                    course.professor_name = professor_name
                    db.session.commit()
                    flash("Course updated successfully!", "success")
                else:
                    flash("Course not found!", "danger")
            elif action == 'delete':
                # Delete Course
                course = Course.query.get(course_id)
                if course:
                    db.session.delete(course)
                    db.session.commit()
                    flash("Course deleted successfully!", "success")
                else:
                    flash("Course not found!", "danger")

        # Get all course update and return information back 
        courses = Course.query.all()
        return render_template('edit_course.html', courses=courses)

