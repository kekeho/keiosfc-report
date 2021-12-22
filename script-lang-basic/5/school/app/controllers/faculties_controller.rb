class FacultiesController < ApplicationController
  def show
    @faculty = Faculty.find(params[:id])
    @students = @faculty.students
  end
end
