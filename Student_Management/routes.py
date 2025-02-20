from flask import render_template, request, redirect, flash, jsonify
from models import Course, Student, db
from sqlalchemy import or_

def init_app(app):
    @app.route('/')
    def home():
        students = Student.query.all()
        courses = Course.query.all()
        return render_template('index.html', students=students, courses=courses)

    @app.route('/students')
    def student_list():
        # Get query parameters for sorting, filtering, and pagination
        sort_by = request.args.get('sort_by', 'id')
        search_query = request.args.get('search', '')
        page = request.args.get('page', 1, type=int)
        per_page = request.args.get('per_page', 10, type=int)

        # Base query
        query = Student.query

        # Apply search filter
        if search_query:
            query = query.filter(or_(
                Student.name.ilike(f'%{search_query}%'),
                Student.email.ilike(f'%{search_query}%')
            ))

        # Apply sorting
        if sort_by == 'name':
            query = query.order_by(Student.name.asc())
        else:
            query = query.order_by(Student.id.asc())

        # Apply pagination
        paginated_students = query.paginate(page=page, per_page=per_page, error_out=False)
        
        # Get all courses for the dropdown
        courses = Course.query.all()

        return render_template('student_list.html', students=paginated_students.items, courses=courses, active_page='students')
    
    @app.route('/assign_course', methods=['POST'])
    def assign_course():
        student_id = request.form.get('student_id')
        course_id = request.form.get('course_id')

        if not student_id or not course_id:
            flash("Student ID and Course ID are required!", "danger")
        else:
            student = Student.query.get(student_id)
            course = Course.query.get(course_id)

            if student and course:
                student.course_id = course.id
                db.session.commit()
                flash("Course assigned successfully!", "success")
            else:
                flash("Student or Course not found!", "danger")

        return redirect('/students')

    @app.route('/edit_course', methods=['GET', 'POST'])
    def edit_course():
        if request.method == 'POST':
            action = request.form.get('action')
            course_id = request.form.get('course_id')
            course_name = request.form.get('course_name')
            professor_name = request.form.get('professor_name')

            if action == 'add':
                if not course_id or not course_name or not professor_name:
                    flash("All fields are required!", "danger")
                else:
                    existing_course = Course.query.get(course_id)
                    if existing_course:
                        flash("Course ID already exists!", "danger")
                    else:
                        new_course = Course(id=course_id, name=course_name, professor_name=professor_name)
                        db.session.add(new_course)
                        db.session.commit()
                        flash("Course added successfully!", "success")
            elif action == 'update':
                course = Course.query.get(course_id)
                if course:
                    course.name = course_name
                    course.professor_name = professor_name
                    db.session.commit()
                    flash("Course updated successfully!", "success")
                else:
                    flash("Course not found!", "danger")
            elif action == 'delete':
                course = Course.query.get(course_id)
                if course:
                    db.session.delete(course)
                    db.session.commit()
                    flash("Course deleted successfully!", "success")
                else:
                    flash("Course not found!", "danger")

        courses = Course.query.all()
        return render_template('edit_course.html', courses=courses)

    @app.route('/api/courses/<string:id>', methods=['PUT'])
    def update_course(id):
        course = Course.query.get_or_404(id)
        data = request.get_json()

        if 'name' in data:
            course.name = data['name']
        if 'professor_name' in data:
            course.professor_name = data['professor_name']

        db.session.commit()
        return jsonify({'message': 'Course updated successfully', 'course': {'id': course.id, 'name': course.name, 'professor_name': course.professor_name}})

    @app.route('/api/courses/<string:id>', methods=['PATCH'])
    def patch_course(id):
        course = Course.query.get_or_404(id)
        data = request.get_json()

        if 'name' in data:
            course.name = data['name']
        if 'professor_name' in data:
            course.professor_name = data['professor_name']

        db.session.commit()
        return jsonify({'message': 'Course partially updated successfully', 'course': {'id': course.id, 'name': course.name, 'professor_name': course.professor_name}})
    
    @app.route('/api/courses/<string:id>', methods=['DELETE'])
    def delete_course(id):
        course = Course.query.get_or_404(id)
        db.session.delete(course)
        db.session.commit()
        return jsonify({'message': 'Course deleted successfully'})
    
    @app.route('/api/courses', methods=['OPTIONS'])
    def courses_options():
        response = jsonify({
            'methods': ['GET', 'POST', 'PUT', 'PATCH', 'DELETE', 'OPTIONS'],
            'description': 'Manage courses in the system'
        })
        response.headers.add('Allow', 'GET, POST, PUT, PATCH, DELETE, OPTIONS')
        return response
    
    @app.route('/students', methods=['GET'])
    def get_students():
        # Get query parameters for sorting, filtering, and pagination
        sort_by = request.args.get('sort_by', 'id')  # Default sort by 'id'
        search_query = request.args.get('search', '')  # Search query
        page = request.args.get('page', 1, type=int)  # Page number
        per_page = request.args.get('per_page', 10, type=int)  # Students per page

        # Base query
        query = Student.query

        # Apply search filter
        if search_query:
            query = query.filter(or_(
                Student.name.ilike(f'%{search_query}%'),
                Student.email.ilike(f'%{search_query}%')
            ))

        # Apply sorting
        if sort_by == 'name':
            query = query.order_by(Student.name.asc())
        else:
            query = query.order_by(Student.id.asc())

        # Apply pagination
        paginated_students = query.paginate(page=page, per_page=per_page, error_out=False)

        # Render the template with paginated students
        return render_template('student_list.html', students=paginated_students.items)

    @app.route('/api/students', methods=['GET'])
    def api_get_students():
        sort_by = request.args.get('sort_by', 'id')
        search_query = request.args.get('search', '')
        page = request.args.get('page', 1, type=int)
        per_page = request.args.get('per_page', 10, type=int)

        query = Student.query

        if search_query:
            query = query.filter(or_(
                Student.name.ilike(f'%{search_query}%'),
                Student.email.ilike(f'%{search_query}%')
            ))

        if sort_by == 'name':
            query = query.order_by(Student.name.asc())
        else:
            query = query.order_by(Student.id.asc())

        paginated_students = query.paginate(page=page, per_page=per_page, error_out=False)

        students_data = [{
            'id': student.id,
            'name': student.name,
            'email': student.email
        } for student in paginated_students.items]

        return jsonify({
            'students': students_data,
            'total_pages': paginated_students.pages,
            'current_page': paginated_students.page,
            'total_students': paginated_students.total
        })
    
    @app.route('/api/students/<int:id>', methods=['PUT'])
    def update_student(id):
        student = Student.query.get_or_404(id)
        data = request.get_json()

        if 'name' in data:
            student.name = data['name']
        if 'email' in data:
            student.email = data['email']
        if 'course_id' in data:
            student.course_id = data['course_id']

        db.session.commit()
        return jsonify({'message': 'Student updated successfully', 'student': {'id': student.id, 'name': student.name, 'email': student.email}})
    
    @app.route('/api/students/<int:id>', methods=['PATCH'])
    def patch_student(id):
        student = Student.query.get_or_404(id)
        data = request.get_json()

        if 'name' in data:
            student.name = data['name']
        if 'email' in data:
            student.email = data['email']
        if 'course_id' in data:
            student.course_id = data['course_id']

        db.session.commit()
        return jsonify({'message': 'Student partially updated successfully', 'student': {'id': student.id, 'name': student.name, 'email': student.email}})
    
    @app.route('/api/students/<int:id>', methods=['DELETE'])
    def delete_student(id):
        student = Student.query.get_or_404(id)
        db.session.delete(student)
        db.session.commit()
        return jsonify({'message': 'Student deleted successfully'})
    
    @app.route('/api/students', methods=['OPTIONS'])
    def students_options():
        response = jsonify({
            'methods': ['GET', 'POST', 'PUT', 'PATCH', 'DELETE', 'OPTIONS'],
            'description': 'Manage students in the system'
        })
        response.headers.add('Allow', 'GET, POST, PUT, PATCH, DELETE, OPTIONS')
        return response
    
    @app.route('/add_delete_student', methods=['GET', 'POST'])
    def add_delete_student():
        if request.method == 'POST':
            action = request.form.get('action')
            student_id = request.form.get('id')
            student_name = request.form.get('name')
            student_email = request.form.get('email')

            if action == 'add':
                if not student_name or not student_email:
                    flash("All fields are required!", "danger")
                else:
                    existing_student = Student.query.filter_by(email=student_email).first()
                    if existing_student:
                        flash("A student with this email already exists!", "danger")
                    else:
                        new_student = Student(name=student_name, email=student_email)
                        db.session.add(new_student)
                        db.session.commit()
                        flash("Student added successfully!", "success")
            elif action == 'update':
                student = Student.query.get(student_id)
                if student:
                    student.name = student_name
                    student.email = student_email
                    db.session.commit()
                    flash("Student updated successfully!", "success")
                else:
                    flash("Student not found!", "danger")
            elif action == 'delete':
                student = Student.query.get(student_id)
                if student:
                    db.session.delete(student)
                    db.session.commit()
                    flash("Student deleted successfully!", "success")
                else:
                    flash("Student not found!", "danger")

        # Fetch all students to display on the page
        students = Student.query.all()
        return render_template('add_delete_student.html', students=students)