require "test_helper"

class FacultiesControllerTest < ActionDispatch::IntegrationTest
  test "should get show" do
    get faculties_show_url
    assert_response :success
  end
end
