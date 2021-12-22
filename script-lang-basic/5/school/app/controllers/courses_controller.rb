class CoursesController < ApplicationController
  def show
    @course = Course.find(params[:id])
  end

  def showall
    @courses = Course.all
  end
end
