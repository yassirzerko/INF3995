import React from "react";
import {shallow } from "enzyme";
import DroneStatusSummary from "./DroneStatusSummary";
import Table from "@material-ui/core/Table";

let props;

beforeEach(() => {
  props = {};
});

describe("DroneStatusSummary ", () => {
  it("should render initial layout", () => {
    const component = shallow(<DroneStatusSummary {...props} />);
    expect(component.length).toBe(1);
  });

  it("should render two table", () => {
    const component = shallow(<DroneStatusSummary {...props} />);
    expect(component.find(Table).length).toBe(2);
  });
});
